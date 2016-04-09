// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "ShieldBashState.h"
#include "LowerShieldState.h"

void UShieldBashState::OnBeginState()
{
	bAlreadyHit = false;
}
void UShieldBashState::TickState(float DeltaTime)
{
	//FCollisionQueryParams RV_TraceParams = FCollisionObjectQueryParams(FNAME(TEXT("RV_Trace")), true, this); _
	if (TimeSinceStateStarted >= 12 * FPS60ToSeconds && !bAlreadyHit)
	{
		DoShieldBash_Server();
	}
	if (TimeSinceStateStarted >= 19 * FPS60ToSeconds)
	{
		ChangeUpperState(Glad->LowerShield);
	}
	
	TimeSinceStateStarted += DeltaTime;
}

void UShieldBashState::SetAlreadyHit_Server_Implementation()
{
	bAlreadyHit = true;
}
bool UShieldBashState::SetAlreadyHit_Server_Validate()
{
	return true;
}
void UShieldBashState::DoShieldBash_Server_Implementation()
{
	ShieldBashEvent.Broadcast();
}
bool UShieldBashState::DoShieldBash_Server_Validate()
{
	return true;
}