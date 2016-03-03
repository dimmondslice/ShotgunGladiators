#include "Shotgun_Prototype.h"
#include "Gladiator.h"
#include "Shotgun_PrototypeProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"

#include "UpperBodyState.h"
#include "LowerBodyState.h"

#include "IdleState.h"
#include "ShootingState.h"
#include "ReloadingState.h"
#include "RaiseShieldState.h"
#include "LowerShieldState.h"
#include "HoldingShieldState.h"
#include "ShieldBashState.h"

#include "WalkingState.h"
#include "DodgeState.h"
#include "JumpCrouchState.h"
#include "FallingState.h"
#include "LandingState.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AGladiator

AGladiator::AGladiator()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->AttachTo(Mesh1P, TEXT("GripPoint"), EAttachLocation::SnapToTargetIncludingScale, true);


	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)


	Idle = CreateDefaultSubobject<UIdleState>(TEXT("IdleState"));
	Shooting = CreateDefaultSubobject<UShootingState>(TEXT("ShootingState"));
	Reloading = CreateDefaultSubobject<UReloadingState>(TEXT("ReloadingState"));
	RaisingShield = CreateDefaultSubobject<URaiseShieldState>(TEXT("RaisingShield"));
	LowerShield = CreateDefaultSubobject<ULowerShieldState>(TEXT("LowerShield"));
	HoldingShield = CreateDefaultSubobject<UHoldingShieldState>(TEXT("HoldingShield"));
	ShieldBash = CreateDefaultSubobject<UShieldBashState>(TEXT("ShieldBash"));

	Walking = CreateDefaultSubobject<UWalkingState>(TEXT("WalkingState"));
	Dodge = CreateDefaultSubobject<UDodgeState>(TEXT("DodgeState"));
	JumpCrouch = CreateDefaultSubobject<UJumpCrouchState>(TEXT("JumpCrouch"));
	Falling = CreateDefaultSubobject<UFallingState>(TEXT("FallingState"));
	Landing = CreateDefaultSubobject<ULandingState>(TEXT("Landing"));

	CurrentUpperState = Idle;
	CurrentLowerState = Walking;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGladiator::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AGladiator::TouchStarted);
	if (EnableTouchscreenMovement(InputComponent) == false)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AGladiator::OnFire);
	}

	//InputComponent->BindAxis("MoveForward", this, &AGladiator::MoveForward);
	//InputComponent->BindAxis("MoveRight", this, &AGladiator::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AGladiator::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AGladiator::LookUpAtRate);
}

void AGladiator::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AShotgun_PrototypeProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

}

void AGladiator::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AGladiator::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

void AGladiator::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
	{
		if (TouchItem.bIsPressed)
		{
			if (GetWorld() != nullptr)
			{
				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
				if (ViewportClient != nullptr)
				{
					FVector MoveDelta = Location - TouchItem.Location;
					FVector2D ScreenSize;
					ViewportClient->GetViewportSize(ScreenSize);
					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
					if (ScaledDelta.X != 0.0f)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.X * BaseTurnRate;
						AddControllerYawInput(Value);
					}
					if (ScaledDelta.Y != 0.0f)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.Y* BaseTurnRate;
						AddControllerPitchInput(Value);
					}
					TouchItem.Location = Location;
				}
				TouchItem.Location = Location;
			}
		}
	}
}

void AGladiator::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AGladiator::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AGladiator::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGladiator::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AGladiator::EnableTouchscreenMovement(class UInputComponent* InputComponent)
{
	bool bResult = false;
	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		bResult = true;
		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AGladiator::BeginTouch);
		InputComponent->BindTouch(EInputEvent::IE_Released, this, &AGladiator::EndTouch);
		InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AGladiator::TouchUpdate);
	}
	return bResult;
}

void AGladiator::Tick(float DeltaSeconds)
{
	//update current states
	CurrentUpperState->TickState(DeltaSeconds);
	CurrentLowerState->TickState(DeltaSeconds);
}

void AGladiator::ChangeUpperState(UUpperBodyState* newState)
{
	CurrentUpperState->ChangeUpperState(newState);
}

void AGladiator::ChangeLowerState(ULowerBodyState* newState)
{
	CurrentLowerState->ChangeLowerState(newState);
}
