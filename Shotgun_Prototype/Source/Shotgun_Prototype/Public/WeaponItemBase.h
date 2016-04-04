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

    //virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) override;

    virtual void BeginPlay() override;
	
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
        int32 maxAmmo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
        int32 currentAmmo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
        int32 magazineSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
        int32 shotsInMagazine;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
        float reloadTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
        float fireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
        float isReloading;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
        float isOnFireCooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
        float spread;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float range;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
        float baseDamage;


    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
    void Reload();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
    void Fire();
    
};
