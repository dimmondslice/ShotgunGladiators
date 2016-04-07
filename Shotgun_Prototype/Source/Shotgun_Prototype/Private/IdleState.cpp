// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "IdleState.h"
#include "RaiseShieldState.h"
#include "ReloadingState.h"

void UIdleState::TickState(float DeltaTime)
{
}

void UIdleState::ProcessInput(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("idle state processinput"))

	if (Glad->bShieldAction)
	{
		ChangeUpperState(Glad->RaisingShield);
	}
	if (Glad->bReloadAction)
	{
		//UE_LOG(LogTemp, Warning, TEXT("reload action!!!!!!!"))
		ChangeUpperState(Glad->Reloading);
	}
}
