// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "ReloadingState.h"
#include "WeaponItemBase.h"
#include "IdleState.h"


void UReloadingState::OnBeginState() 
{
	//broadcast fn to play anim

    //UE_LOG(LogTemp, Error, TEXT("Enter Reload"));
    BeginReloadEvent.Broadcast();
}

void UReloadingState::OnStopState()
{
    //UE_LOG(LogTemp, Error, TEXT("Exit Reload"));
    EndReloadEvent.Broadcast();
}

void UReloadingState::TickState(float DeltaTime)
{
    TimeSinceStateStarted += DeltaTime;
    //UE_LOG(LogTemp, Error, TEXT("ticking"));

	if (TimeSinceStateStarted >= reloadTime)
	{
		//broadcast thatperState()
        ChangeUpperState(Glad->Idle);
	}

}

bool UReloadingState::Get_bCanUse()
{
    
    return true;


    /*
	//if the mag is already full
	if (Glad->HeldWeapon->shotsInMagazine >= Glad->HeldWeapon->magazineSize)
	{
		bCanUse = false;
		return false;
	}
	//if the gun has no more ammo
	else if (Glad->HeldWeapon->currentAmmo <= 0)
	{
		bCanUse = false;
		return false;
	}
	else
	{
		bCanUse = true;
		return true;
	}
    */
}