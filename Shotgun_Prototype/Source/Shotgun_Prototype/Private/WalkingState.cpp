// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "WalkingState.h"
#include "JumpCrouchState.h"


void UWalkingState::TickState(float DeltaTime)
{
	   
}

void UWalkingState::ProcessInput()
{
	Super::ProcessInput();
	if (Owner->bJumpInput)
	{
		ChangeLowerState(Owner->JumpCrouch);
	}

	Owner->MoveForward(InputComp->GetAxisValue(TEXT("MoveForward")));
	Owner->MoveRight(InputComp->GetAxisValue(TEXT("MoveRight")));
}
