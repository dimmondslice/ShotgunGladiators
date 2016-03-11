// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "WalkingState.h"
#include "JumpCrouchState.h"


void UWalkingState::TickState(float DeltaTime)
{
	   
}

void UWalkingState::ProcessInput(float DeltaTime)
{
	Super::ProcessInput(DeltaTime);
	if (Owner->bJumpAction)
	{
		ChangeLowerState(Owner->JumpCrouch);
	}
	float xSpeed = Owner->MoveForwardAxis * Owner->WalkSpeed;
	float ySpeed = Owner->MoveRightAxis * Owner->WalkSpeed;
	MoveDirection(xSpeed, ySpeed);
}
