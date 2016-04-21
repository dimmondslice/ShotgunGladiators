// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "WalkingState.h"
#include "JumpCrouchState.h"
#include "DodgeState.h"
#include "HoldingShieldState.h"
#include "ShieldBashState.h"
#include "LowerIdleState.h"
#include "iso646.h"

void UWalkingState::TickState(float DeltaTime)
{   
	if ((Glad->MoveForwardAxis == 0) && (Glad->MoveRightAxis == 0))
	{
		ChangeLowerState(Glad->LowerIdle);
	}

	
}

void UWalkingState::ProcessInput(float DeltaTime)
{	
	float xSpeed = Glad->MoveForwardAxis * 30.0f;
	float ySpeed = Glad->MoveRightAxis * 30.0f;
	MoveDirection(xSpeed, ySpeed);

	//we want all the same defualt transitions found in LowerIdle, so just call its process input
	Glad->LowerIdle->ProcessInput(DeltaTime);
}
