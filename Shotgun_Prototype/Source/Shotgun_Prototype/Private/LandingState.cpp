// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "LandingState.h"
#include "WalkingState.h"

void ULandingState::TickState(float DeltaTime)
{
	TimeSinceStateStarted += DeltaTime;
	if (TimeSinceStateStarted > 4 * FPS60ToSeconds)
		ChangeLowerState(Glad->Walking);
}

void ULandingState::ProcessInput(float DeltaTime)
{
}
