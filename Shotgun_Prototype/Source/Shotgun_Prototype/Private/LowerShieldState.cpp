// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "LowerShieldState.h"
#include "IdleState.h"
#include "ShieldItemBase.h"

void ULowerShieldState::OnBeginState()
{
	DestroyShieldEvent.Broadcast();
}
void ULowerShieldState::TickState(float DeltaTime)
{
	if (TimeSinceStateStarted >= 11 * FPS60ToSeconds)
	{
		DestroyShield_Server();
		//DestroyShieldEvent.Broadcast();
		ChangeUpperState(Glad->Idle);
	}
	TimeSinceStateStarted += DeltaTime;
}

void ULowerShieldState::DestroyShield_Server_Implementation()
{
	Glad->HeldShield->Destroy();
}
bool ULowerShieldState::DestroyShield_Server_Validate()
{
	return true;
}
