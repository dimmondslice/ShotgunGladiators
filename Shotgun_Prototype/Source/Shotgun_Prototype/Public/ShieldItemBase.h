// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemBase.h"
#include "ShieldItemBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API AShieldItemBase : public AItemBase
{
    GENERATED_BODY()

public:

    //UPROPERTY(BlueprintReadWrite, Category = "Shield|Hit Effects")
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield|Effects")
    UParticleSystem* HitEffects;
	
};
