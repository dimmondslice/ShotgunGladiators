// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "WeaponItemBase.h"


AWeaponItemBase::AWeaponItemBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AWeaponItemBase::BeginPlay() {
    Super::BeginPlay();
}

void AWeaponItemBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

