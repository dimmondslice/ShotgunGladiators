// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "GladiatorAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories=AnimInstance, BlueprintType)
class SHOTGUN_PROTOTYPE_API UGladiatorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

    APawn* OwningPawn;

    virtual void NativeInitializeAnimation() override;
	
    virtual void NativeUpdateAnimation(float DeltaTimeX) override;
	
};
