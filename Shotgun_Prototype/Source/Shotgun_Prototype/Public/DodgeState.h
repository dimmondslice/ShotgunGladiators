// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LowerBodyState.h"
#include "DodgeState.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API UDodgeState : public ULowerBodyState
{
	GENERATED_BODY()

public:
	UDodgeState();
public:
	UPROPERTY(EditAnywhere)
	float DodgeForce;			//How strong is the sideways dodgeforce
	UPROPERTY(EditAnywhere)
	float PopForce;				//How much will the gladiator be popped up when dodging
	UPROPERTY(EditAnywhere)
	int32 MaxNumOfCharges;
	UPROPERTY(EditAnywhere)
	float RechargeTime;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 CurrentChargesRemaining;
private:
	
	float CurrentRechargeTimer;
	bool bExecutedDodge;

public:
    
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDodgeEventDelegate);

    UPROPERTY(BlueprintAssignable, Category = "Gladiator State/Dodge")
    FDodgeEventDelegate BeginDodgeEvent;
    
    UPROPERTY(BlueprintAssignable, Category = "Gladiator State/Dodge")
    FDodgeEventDelegate BeginDodgeAnimEvent;

    UPROPERTY(BlueprintAssignable, Category = "Gladiator State/Dodge")
    FDodgeEventDelegate EndDodgeEvent;


	virtual void TickState(float DeltaTime) override;
	virtual void ProcessInput(float DeltaTime) override;
	virtual void OnBeginState() override;
    virtual void OnStopState() override;
	virtual bool Get_bCanUse() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ExecuteDodge();

};
