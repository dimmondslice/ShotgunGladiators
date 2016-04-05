// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpperBodyState.h"
#include "LowerShieldState.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API ULowerShieldState : public UUpperBodyState
{
	GENERATED_BODY()
	
public:
	virtual void OnBeginState() override;
	virtual void TickState(float DeltaTime) override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDestroyShieldDelegate);
	UPROPERTY(BlueprintAssignable, Category = "Gladiator")
	FDestroyShieldDelegate DestroyShieldEvent;
	
};
