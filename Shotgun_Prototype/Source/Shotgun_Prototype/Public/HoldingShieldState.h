// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpperBodyState.h"
#include "HoldingShieldState.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API UHoldingShieldState : public UUpperBodyState
{
	GENERATED_BODY()

public:
	virtual void TickState(float DeltaTime) override;
	
	
};
