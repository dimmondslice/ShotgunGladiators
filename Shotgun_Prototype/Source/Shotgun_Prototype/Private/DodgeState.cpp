// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "DodgeState.h"

void UDodgeState::TickState(float DeltaTime)
{
}

void UDodgeState::ProcessInput(float DeltaTime)
{
}

void UDodgeState::OnBeginState()
{
	UE_LOG(LogTemp, Warning, TEXT("begin state dodge"));
	MoveDirection(100000.f, 100000.f);

	if (Owner->GetRootComponent()->IsSimulatingPhysics())
	{
		UE_LOG(LogTemp, Warning, TEXT("heyyoo"));
	}
}
