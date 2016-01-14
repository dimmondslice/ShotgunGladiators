// Fill out your copyright notice in the Description page of Project Settings.

#include "GitTest.h"
#include "PawnWithCamera.h"


// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Create this actors components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->AttachTo(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 400.f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	//create and attach the camera
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->AttachTo(OurCameraSpringArm, USpringArmComponent::SocketName);

	//take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//default speed values
	ForwardSpeed = 300.0f;
	StrafeSpeed = 200.0f;
	//default look sensitivity
	LookSensitivityX = 2.0f;
	LookSensitivityY = 2.0f;
}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithCamera::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//zooming in and out code
	if (bZoomingIn)
	{
		ZoomFactor += DeltaTime / 0.5f;		//zoom in over half a second
	}
	else
	{
		ZoomFactor -= DeltaTime / 0.25f; // zoom out over a quater of a second
	}
	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
	//blend our camera's FOV and our springArms length based on zoomfactor
	OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);

	//camera control code
	{
		//rotate our actor's yaw which will turn our camera because we're attached to it
		FRotator newRot = GetActorRotation();
		newRot.Yaw += CameraInput.X;
		SetActorRotation(newRot);
		//rotate the camera's pitch, but limit it so we're always looking downward
		FRotator newRot2 = OurCameraSpringArm->GetComponentRotation();
		newRot2.Pitch = FMath::Clamp(newRot2.Pitch + CameraInput.Y, -80.0f, -15.0f);
		//newRot.Roll = FMath::Clamp()
		OurCameraSpringArm->SetWorldRotation(newRot2);
	}

	//handle movememnt based on out movex and movey axes
	if (!MovementInput.IsZero())
	{
		//scale our moevement input axis values by 100 units per second
		MovementInput = MovementInput.GetSafeNormal();
		FVector newLoc = GetActorLocation();
		newLoc += GetActorForwardVector() * MovementInput.X * DeltaTime * ForwardSpeed;
		newLoc += GetActorRightVector() * MovementInput.Y * DeltaTime * StrafeSpeed;
		SetActorLocation(newLoc);

		//also slightly roll the camera when the player strafes
		FRotator newRot = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 0.0f);
		newRot.Roll += MovementInput.Y * DeltaTime * StrafeSpeed;
	}
}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	//yes this following code block was literally copied from the tutorial, I didn't feel like writing it all, it's literally just binding inputs to their respective functions
	//Hook up events for "ZoomIn"
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &APawnWithCamera::ZoomOut);

	//Hook up every-frame handling for our four axes
	InputComponent->BindAxis("MoveForward", this, &APawnWithCamera::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APawnWithCamera::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &APawnWithCamera::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &APawnWithCamera::YawCamera);
}

void APawnWithCamera::MoveForward(float AxisVal)
{
	MovementInput.X = FMath::Clamp<float>(AxisVal, -1.0f,1.0f);
}
void APawnWithCamera::MoveRight(float AxisVal)
{
	MovementInput.Y = FMath::Clamp<float>(AxisVal, -1.0f, 1.0f);
}
void APawnWithCamera::PitchCamera(float AxisVal)
{
	CameraInput.Y = AxisVal * LookSensitivityY;
}
void APawnWithCamera::YawCamera(float AxisVal)
{
	CameraInput.X = AxisVal * LookSensitivityX;
}
void APawnWithCamera::ZoomIn()
{
	bZoomingIn = true;
}
void APawnWithCamera::ZoomOut()
{
	bZoomingIn = false;
}



