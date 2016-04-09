// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LowerBodyState.h"
#include "FallingState.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API UFallingState : public ULowerBodyState
{
	GENERATED_BODY()
	
	virtual void TickState(float DeltaTime) override;
	virtual void ProcessInput(float DeltaTime) override;

	virtual void OnBeginState() override;
};
