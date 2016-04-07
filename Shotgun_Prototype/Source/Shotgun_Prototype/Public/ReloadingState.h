// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpperBodyState.h"
#include "ReloadingState.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API UReloadingState : public UUpperBodyState
{
	GENERATED_BODY()

public:
	virtual void OnBeginState() override;
    virtual void OnStopState() override;
	virtual void TickState(float DeltaTime) override;
	virtual bool Get_bCanUse() override;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReloadStateEvent);

    UPROPERTY(BlueprintAssignable, Category = "Gladiator State")
    FReloadStateEvent BeginReloadEvent;

    UPROPERTY(BlueprintAssignable, Category = "Gladiator State")
    FReloadStateEvent EndReloadEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gladiator State")
    float reloadTime;
};
