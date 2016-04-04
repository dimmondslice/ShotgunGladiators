// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "LowerShieldState.h"

void ULowerShieldState::OnBeginState()
{
	DestroyShieldEvent.Broadcast();
}
void ULowerShieldState::TickState(float DeltaTime)
{
}
