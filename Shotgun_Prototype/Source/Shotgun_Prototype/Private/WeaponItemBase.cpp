// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun_Prototype.h"
#include "WeaponItemBase.h"
//#include "Engine.h"

#include "UnrealNetwork.h"


AWeaponItemBase::AWeaponItemBase()
{
    PrimaryActorTick.bCanEverTick = true;

    //bReplicates = true;
}


void AWeaponItemBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

//Signal variables for replication

    //INTS
    DOREPLIFETIME(AWeaponItemBase, maxAmmo);
    DOREPLIFETIME(AWeaponItemBase, currentAmmo);
    DOREPLIFETIME(AWeaponItemBase, magazineSize);
    DOREPLIFETIME(AWeaponItemBase, shotsInMagazine);

    //FLOATS
    DOREPLIFETIME(AWeaponItemBase, reloadTime);
    DOREPLIFETIME(AWeaponItemBase, fireRate);
    DOREPLIFETIME(AWeaponItemBase, spread);
    DOREPLIFETIME(AWeaponItemBase, range);
    DOREPLIFETIME(AWeaponItemBase, baseDamage);

    //BOOLS
    DOREPLIFETIME(AWeaponItemBase, isReloading);
    DOREPLIFETIME(AWeaponItemBase, isOnFireCooldown);

}


void AWeaponItemBase::BeginPlay() {
    Super::BeginPlay();
}

void AWeaponItemBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    this->Fire();
    //this->Fire_Implementation();
    //UE_LOG(LogTemp, Error, TEXT("yo fire c++"));

}

/*
void AWeaponItemBase::Reload() {

}
*/

void AWeaponItemBase::Reload_Implementation() {

}

/*
void AWeaponItemBase::Fire() {

}
*/

void AWeaponItemBase::Fire_Implementation() {
    //UE_LOG(LogTemp, Error, TEXT("yo fire c++"));
}