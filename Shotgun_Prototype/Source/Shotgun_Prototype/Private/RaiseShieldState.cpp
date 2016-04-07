// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "RaiseShieldState.h"

#include "HoldingShieldState.h"

void URaiseShieldState::OnBeginState()
{
	
}

void URaiseShieldState::TickState(float DeltaTime)
{
	
	if (TimeSinceStateStarted > 6 * FPS60ToSeconds)
	{
		SpawnShield_Server();
		ChangeUpperState(Glad->HoldingShield);
	}

	//increment time since started
	TimeSinceStateStarted += DeltaTime;
}

void URaiseShieldState::SpawnShield_Server_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("raise shield tick state"));
	SpawnShieldEvent.Broadcast();
}
bool URaiseShieldState::SpawnShield_Server_Validate()
{
	return true;
}
