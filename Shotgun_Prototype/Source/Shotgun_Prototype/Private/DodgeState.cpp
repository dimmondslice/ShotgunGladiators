// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "DodgeState.h"
#include "walkingState.h"
#include "FallingState.h"

UDodgeState::UDodgeState()
{
	CurrentRechargeTimer = RechargeTime;
	bExecutedDodge = false;
}
bool UDodgeState::Get_bCanUse()
{
	//update the ability to use this state
	if (CurrentChargesRemaining <= 0)
	{
		bCanUse = false;
		return bCanUse;
	}
	else
	{
		bCanUse = true;
		return bCanUse;
	}
}
void UDodgeState::OnBeginState()
{
    BeginDodgeAnimEvent.Broadcast();
}

void UDodgeState::OnStopState()
{
    EndDodgeEvent.Broadcast();
}

void UDodgeState::TickState(float DeltaTime)
{
	TimeSinceStateStarted += DeltaTime;
	if (TimeSinceStateStarted >= 15 * FPS60ToSeconds)
	{
		ChangeLowerState(Glad->Falling);
		bExecutedDodge = false;
		return;
	}
	else if (TimeSinceStateStarted > 6 * FPS60ToSeconds && !bExecutedDodge)
	{
		ExecuteDodge();
	}
}

void UDodgeState::ProcessInput(float DeltaTime)
{
}

void UDodgeState::ExecuteDodge()
{
	bExecutedDodge = true;
	//decrement number of times you can use the charge
	CurrentChargesRemaining -= 1;
	//reset the timer, no extra dodges for you!
	CurrentRechargeTimer = RechargeTime;

	//create dodge direction by adding your forward vector and right vector Multiplied by your stick direction
	FVector LaunchDir = Glad->GetActorForwardVector() * Glad->MoveForwardAxis +
		Glad->GetActorRightVector() * Glad->MoveRightAxis;
	if (LaunchDir.IsNearlyZero())
		LaunchDir = Glad->GetActorForwardVector();
	LaunchDir *= DodgeForce;
	LaunchDir.Z = PopForce;		//add a little bit of upward force to"pop" the character up a little
	Glad->LaunchCharacter_Server(LaunchDir, false, false);

	//BeginDodgeEvent();
	BeginDodgeEvent.Broadcast();
}

void UDodgeState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	CurrentRechargeTimer -= DeltaTime;
	//if the recharge timer hits zero, add a new charge, and reset the timer
	if (CurrentRechargeTimer <= 0.0f)
	{
		if (CurrentChargesRemaining < MaxNumOfCharges)
			CurrentChargesRemaining++;
		CurrentRechargeTimer = RechargeTime;
	}
	//UE_LOG(LogTemp, Warning, TEXT("current charges remaining %i"), CurrentChargesRemaining);
}