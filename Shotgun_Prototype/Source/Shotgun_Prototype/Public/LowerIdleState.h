// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LowerBodyState.h"
#include "LowerIdleState.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API ULowerIdleState : public ULowerBodyState
{
	GENERATED_BODY()

public:
	virtual void TickState(float DeltaTime) override;
	virtual void ProcessInput(float DeltaTime) override;

};
