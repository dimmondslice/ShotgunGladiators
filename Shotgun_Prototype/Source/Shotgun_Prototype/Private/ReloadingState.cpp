// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "ReloadingState.h"
#include "WeaponItemBase.h"
#include "IdleState.h"


void UReloadingState::OnBeginState() 
{
	//broadcast fn to play anim
}
void UReloadingState::TickState(float DeltaTime)
{
	if (TimeSinceStateStarted >= 30 * FPS60ToSeconds)
	{
		//broadcast thatperState()
		//ChangeUppper(Owner->Idle)
	
	}
		

	TimeSinceStateStarted += DeltaTime;
}

bool UReloadingState::Get_bCanUse()
{
	//if the mag is already full
	if (Owner->HeldWeapon->shotsInMagazine >= Owner->HeldWeapon->magazineSize)
	{
		bCanUse = false;
		return false;
	}
	//if the gun has no more ammo
	else if (Owner->HeldWeapon->currentAmmo <= 0)
	{
		bCanUse = false;
		return false;
	}
	else
	{
		bCanUse = true;
		return true;
	}
}


