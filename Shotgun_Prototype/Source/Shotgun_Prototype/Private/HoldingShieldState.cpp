// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "HoldingShieldState.h"

#include "LowerShieldState.h"

void UHoldingShieldState::TickState(float DeltaTime)
{
	if (!Glad->bShieldAction)
	{
		ChangeUpperState(Glad->LowerShield);
	}
}

