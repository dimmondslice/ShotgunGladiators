// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "RaiseShieldState.h"

#include "HoldingShieldState.h"

void URaiseShieldState::OnBeginState()
{
	
}

void URaiseShieldState::TickState(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("raise shield tick state"))
	if (TimeSinceStateStarted > 6 * FPS60ToSeconds)
	{
		SpawnShieldEvent.Broadcast();
		ChangeUpperState(Owner->HoldingShield);
	}
}
