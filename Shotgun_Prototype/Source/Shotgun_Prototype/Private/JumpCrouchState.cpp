// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "JumpCrouchState.h"
#include "FallingState.h"

void UJumpCrouchState::OnBeginState()
{
	Owner->Jump();
	ChangeLowerState(Owner->Falling);
}
void UJumpCrouchState::TickState(float DeltaTime)
{

}

void UJumpCrouchState::ProcessInput(float DeltaTime)
{
}


