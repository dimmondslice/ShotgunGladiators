// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpperBodyState.h"
#include "IdleState.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API UIdleState : public UUpperBodyState
{
	GENERATED_BODY()
	
	virtual void TickState(float DeltaTime) override;
	virtual void ProcessInput() override;
	
	
};
