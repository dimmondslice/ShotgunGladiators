

#include "Shotgun_Prototype.h"
#include "UnrealNetwork.h"

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

#include "LowerIdleState.h"
#include "WalkingState.h"
#include "DodgeState.h"
#include "JumpCrouchState.h"
#include "FallingState.h"
#include "LandingState.h"

#include "ShieldItemBase.h"

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

	LowerIdle = CreateDefaultSubobject<ULowerIdleState>(TEXT("LowerIdle"));
	Walking = CreateDefaultSubobject<UWalkingState>(TEXT("WalkingState"));
	Dodge = CreateDefaultSubobject<UDodgeState>(TEXT("DodgeState"));
	JumpCrouch = CreateDefaultSubobject<UJumpCrouchState>(TEXT("JumpCrouch"));
	Falling = CreateDefaultSubobject<UFallingState>(TEXT("FallingState"));
	Landing = CreateDefaultSubobject<ULandingState>(TEXT("Landing"));

	CurrentUpperState = Idle;
	CurrentLowerState = LowerIdle;

	WalkSpeed = 10.f;
}

void AGladiator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGladiator, bShieldAction);
    DOREPLIFETIME(AGladiator, bDodgeAction);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGladiator::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AGladiator::SetJumpPressed); // &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AGladiator::SetJumpReleased);// &ACharacter::StopJumping);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AGladiator::SetFirePressed);
	InputComponent->BindAction("Fire", IE_Released, this, &AGladiator::SetFireReleased);
	InputComponent->BindAction("Reload", IE_Pressed, this, &AGladiator::SetReloadPressed);
	InputComponent->BindAction("Reload", IE_Released, this, &AGladiator::SetReloadReleased);
	InputComponent->BindAction("Shield", IE_Pressed, this, &AGladiator::SetShieldPressed);
	InputComponent->BindAction("Shield", IE_Released, this, &AGladiator::SetShieldReleased);
	InputComponent->BindAction("Dodge", IE_Pressed, this, &AGladiator::SetDodgePressed);
	InputComponent->BindAction("Dodge", IE_Released, this, &AGladiator::SetDodgeReleased);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AGladiator::TouchStarted);
	if (EnableTouchscreenMovement(InputComponent) == false)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AGladiator::OnFire);
	}

	//InputComponent->BindAxis("MoveForward", this, &AGladiator::MoveForward);
	//InputComponent->BindAxis("MoveRight", this, &AGladiator::MoveRight);
	InputComponent->BindAxis("MoveForward", this, &AGladiator::SetMoveForwardAxis);
	InputComponent->BindAxis("MoveRight", this, &AGladiator::SetMoveRightAxis);

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

void AGladiator::BeginPlay()
{
	Super::BeginPlay();
	CurrentUpperState = Idle;
	CurrentLowerState = LowerIdle;

	FActorSpawnParameters param;
	//param.
	//HeldShield = GetWorld()->SpawnActor<AShieldItemBase>()
}

//I can't believe I have to have my own bool setting input events.
void AGladiator::SetJumpPressed() { bJumpAction = true; }
void AGladiator::SetJumpReleased() { bJumpAction = false; }
void AGladiator::SetFirePressed() { bFireAction = true; }
void AGladiator::SetFireReleased() { bFireAction = false; }
void AGladiator::SetReloadPressed() { bReloadAction = true; }
void AGladiator::SetReloadReleased() { bReloadAction = false; }

void AGladiator::SetShieldPressed_Implementation() { bShieldAction = true; }
bool AGladiator::SetShieldPressed_Validate() { return true; }

void AGladiator::SetShieldReleased_Implementation() { bShieldAction = false; }
bool AGladiator::SetShieldReleased_Validate() { return true; }

void AGladiator::SetDodgePressed_Implementation() { bDodgeAction = true; }
bool AGladiator::SetDodgePressed_Validate() { return true; }

void AGladiator::SetDodgeReleased_Implementation() { bDodgeAction = false; }
bool AGladiator::SetDodgeReleased_Validate() { return true; }

void AGladiator::SetMoveForwardAxis(float val)
{
	MoveForwardAxis = val;
	MoveAxes.X = val;
}

void AGladiator::SetMoveRightAxis(float val)
{
	MoveRightAxis = val;
	MoveAxes.Y = val;
}

void AGladiator::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    //update current states

	CurrentUpperState->TickState(DeltaSeconds);
	CurrentLowerState->TickState(DeltaSeconds);
	
	//UE_LOG(LogTemp, Warning, TEXT("%s is in %s"), *GetName(), *CurrentLowerState->GetName());
}

void AGladiator::Landed(const FHitResult & Hit)
{
	CurrentLowerState->ChangeLowerState(Landing);
}

void AGladiator::LaunchCharacter_Server_Implementation(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
    //UE_LOG(LogTemp, Warning, TEXT("called implementation"));
    LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);
}
bool AGladiator::LaunchCharacter_Server_Validate(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
    //this function exists and is required for the client to validate itself, to prevent cheating.
    //We're not actually going to implement any check though
    return true;
}

//Update the current Attributes with a Supplied FGladiatorAttribute Struct
    //Server
void AGladiator::ApplyValuesFromAttribute_Implementation(FGladiatorAttributes newAttributes)
{
    ApplyValuesFromAttribute_Multicast(newAttributes);
}
bool AGladiator::ApplyValuesFromAttribute_Validate(FGladiatorAttributes newAttributes)
{
    return true;
}
    //Multicast
void AGladiator::ApplyValuesFromAttribute_Multicast_Implementation(FGladiatorAttributes newAttributes)
{
    //SetWalkSpeed(newAttributes.walkSpeed);
    GetCharacterMovement()->MaxWalkSpeed = newAttributes.walkSpeed;

}
bool AGladiator::ApplyValuesFromAttribute_Multicast_Validate(FGladiatorAttributes newAttributes)
{
    return true;
}


void AGladiator::SetWalkSpeed_Implementation(float speed)
{
    SetWalkSpeed_Multicast(speed);
}

bool AGladiator::SetWalkSpeed_Validate(float speed)
{
    return true;
}

void AGladiator::SetWalkSpeed_Multicast_Implementation(float speed)
{
    GetCharacterMovement()->MaxWalkSpeed = speed;

}
bool AGladiator::SetWalkSpeed_Multicast_Validate(float speed)
{
    return true;
}

void AGladiator::ChangeUpperState(UUpperBodyState* newState)
{
	CurrentUpperState->ChangeUpperState(newState);
}

void AGladiator::ChangeLowerState(ULowerBodyState* newState)
{
	CurrentLowerState->ChangeLowerState(newState);
}
