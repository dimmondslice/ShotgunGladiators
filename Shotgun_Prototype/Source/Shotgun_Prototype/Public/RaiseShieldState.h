// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpperBodyState.h"
#include "RaiseShieldState.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API URaiseShieldState : public UUpperBodyState
{
	GENERATED_BODY()

public:
	virtual void OnBeginState() override;
	virtual void TickState(float DeltaTime) override;
		
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpawnShieldDelegate);
	UPROPERTY(BlueprintAssignable, Category = "Gladiator")
	FSpawnShieldDelegate SpawnShieldEvent;

	UFUNCTION(Server, Reliable, WithValidation)
	void SpawnShield_Server();

};
