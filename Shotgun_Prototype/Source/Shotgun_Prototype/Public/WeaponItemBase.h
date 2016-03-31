// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemBase.h"
#include "WeaponItemBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SHOTGUN_PROTOTYPE_API AWeaponItemBase : public AItemBase
{
    GENERATED_BODY()

public:

    AWeaponItemBase();

    virtual void BeginPlay() override;
	
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon Item")
    void Reload();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon Item")
    void Fire();
    
};
