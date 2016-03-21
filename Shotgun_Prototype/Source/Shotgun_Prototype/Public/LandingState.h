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
	
	virtual void TickState(float DeltaTime) override;
	virtual void ProcessInput() override;
};
