// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "LandingState.h"
#include "WalkingState.h"
#include "DodgeState.h"

void ULandingState::TickState(float DeltaTime)
{
	TimeSinceStateStarted += DeltaTime;
	if (TimeSinceStateStarted > LagFrames * FPS60ToSeconds)
		ChangeLowerState(Glad->Walking);
}

void ULandingState::ProcessInput(float DeltaTime)
{
}

void ULandingState::OnBeginState()
{
	if (Glad->PreviousLowerState == Glad->Falling)
	{
		LagFrames = LagAfterFalling;
	}
	else if (Glad->PreviousLowerState == Glad->Dodge)
	{
		LagFrames = LagAFterDodge;
	}
	else
	{
		LagFrames = 4;
	}
}
