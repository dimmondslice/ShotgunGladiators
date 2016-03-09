// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LowerBodyState.h"
#include "WalkingState.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API UWalkingState : public ULowerBodyState
{
	  GENERATED_BODY()

	  virtual void TickState(float DeltaTime) override;
	  virtual void ProcessInput() override;
};
