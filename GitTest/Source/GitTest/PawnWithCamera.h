// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PawnWithCamera.generated.h"

UCLASS()
class GITTEST_API APawnWithCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnWithCamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	UCameraComponent* OurCamera;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* OurCameraSpringArm;
	UPROPERTY(EditAnywhere)
		float ForwardSpeed;
	UPROPERTY(EditAnywhere)
		float StrafeSpeed;
	UPROPERTY(EditAnywhere)
		float LookSensitivityX;
	UPROPERTY(EditAnywhere)
		float LookSensitivityY;


private:
	//input variables
	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;
	//input functions
	void MoveForward(float AxisVal);
	void MoveRight(float AxisVal);
	void PitchCamera(float AxisVal);
	void YawCamera(float AxsiVal);
	void ZoomIn();
	void ZoomOut();
};
