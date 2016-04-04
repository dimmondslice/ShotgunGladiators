// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "IdleState.h"
#include "RaiseShieldState.h"

void UIdleState::TickState(float DeltaTime)
{
}

void UIdleState::ProcessInput(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("idle state processinput"))

	if (Owner->bShieldAction)
	{
		//UE_LOG(LogTemp, Warning, TEXT("shield action!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"))
		ChangeUpperState(Owner->RaisingShield);
	}
}
