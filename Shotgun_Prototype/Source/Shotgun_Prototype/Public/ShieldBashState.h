// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpperBodyState.h"
#include "ShieldBashState.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API UShieldBashState : public UUpperBodyState
{
	GENERATED_BODY()
	
public:
	virtual void OnBeginState() override;
	virtual void TickState(float DeltaTime) override;

	bool bAlreadyHit;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShieldBashDelegate);
	UPROPERTY(BlueprintAssignable, Category = "Gladiator/ShieldBash")
	FShieldBashDelegate ShieldBashEvent;

	UFUNCTION(Server, Reliable, WithValidation)
	void DoShieldBash_Server();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category ="Gladiator/ShieldBash")
	void SetAlreadyHit_Server();
};
