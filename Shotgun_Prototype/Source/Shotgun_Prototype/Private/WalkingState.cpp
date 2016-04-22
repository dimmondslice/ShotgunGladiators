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
	//only switch back to lower idle if you've been in this state long enough to have moved forward if you wanted to
	if (TimeSinceStateStarted > 5 * FPS60ToSeconds)
	{
		if (Glad->GetVelocity().IsNearlyZero())
		{
			ChangeLowerState(Glad->LowerIdle);
		}
	}

	TimeSinceStateStarted += DeltaTime;
}

void UWalkingState::ProcessInput(float DeltaTime)
{	
	float xSpeed = Glad->MoveForwardAxis * 30.0f;
	float ySpeed = Glad->MoveRightAxis * 30.0f;
	MoveDirection(xSpeed, ySpeed);

	Glad->LowerIdle->ProcessInput(DeltaTime);
}
