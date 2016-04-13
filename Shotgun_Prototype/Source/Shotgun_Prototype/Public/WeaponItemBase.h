// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "ShotgunDamageType.h"

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

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    //virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) override;

    virtual void BeginPlay() override;
	
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    int32 maxAmmo;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    int32 currentAmmo;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    int32 magazineSize;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    int32 shotsInMagazine;


    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float reloadTime;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float fireRate;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float spread;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float range;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float baseDamage;


    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    bool isReloading;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    bool isOnFireCooldown;

    //********** Crashes when EditAnywhere is in UPROPERTY **********
        //Don't forget to uncomment Header File
    //UPROPERTY(BlueprintReadWrite, Category = "WeaponStats")
    //UShotgunDamageType* damageType;


    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
    void Reload();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
    void Fire();
    
};
