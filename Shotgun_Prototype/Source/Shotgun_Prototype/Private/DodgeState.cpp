// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "DodgeState.h"
#include "walkingState.h"

UDodgeState::UDodgeState()
{
	CurrentRechargeTimer = RechargeTime;
}

void UDodgeState::TickState(float DeltaTime)
{
}

void UDodgeState::ProcessInput(float DeltaTime)
{
}

void UDodgeState::OnBeginState()
{
	//decrement number of times you can use the charge
	CurrentChargesRemaining-=1;

	//create dodge direction by adding your forward vector and right vector Multiplied by your stick direction
	FVector LaunchDir = Owner->GetActorForwardVector() * Owner->MoveForwardAxis +
		Owner->GetActorRightVector() * Owner->MoveRightAxis;
	if (LaunchDir.IsNearlyZero())
		LaunchDir = Owner->GetActorForwardVector();
	LaunchDir *= DodgeForce;
	LaunchDir.Z = PopForce;		//add a little bit of upward force to"pop" the character up a little
	Owner->LaunchCharacter_Server(LaunchDir, false, false);

    //BeginDodgeEvent();
    BeginDodgeEvent.Broadcast();
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
	UE_LOG(LogTemp, Warning, TEXT("current charges remaining %i"), CurrentChargesRemaining);
}