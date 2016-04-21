// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FallingState.h"
#include "LandingState.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API ULandingState : public UFallingState
{
	GENERATED_BODY()
	
public:

	virtual void TickState(float DeltaTime) override;
	virtual void ProcessInput(float DeltaTime) override;
	virtual void OnBeginState() override;

	//set to one of the lag after variables depending on what the previous state was before this one was activated
	uint8 LagFrames;

	uint8 LagAfterFalling = 4;
	uint8 LagAFterDodge = 20;
};
