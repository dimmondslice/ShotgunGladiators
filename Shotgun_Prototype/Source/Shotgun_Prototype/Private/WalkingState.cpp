// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "WalkingState.h"
#include "JumpCrouchState.h"
#include "DodgeState.h"
#include "HoldingShieldState.h"
#include "ShieldBashState.h"

void UWalkingState::TickState(float DeltaTime)
{   
}

void UWalkingState::ProcessInput(float DeltaTime)
{
	Super::ProcessInput(DeltaTime); 
	
	float xSpeed = Glad->MoveForwardAxis * 30.0f;
	float ySpeed = Glad->MoveRightAxis * 30.0f;
	MoveDirection(xSpeed, ySpeed);

	if (Glad->bJumpAction)
	{
		ChangeLowerState(Glad->JumpCrouch);
	}
	if (Glad->bDodgeAction)
	{
		//if the upper body is shielding then you might want to do a shield bash
		if (Glad->CurrentUpperState == Glad->HoldingShield)
		{
			FVector2D inputVec = FVector2D(Glad->MoveForwardAxis, Glad->MoveRightAxis);
			//if there is no stick input, or forward input, we want to do a shield bash
			if (inputVec == FVector2D::ZeroVector || inputVec.X > 0.0f)
			{
				ChangeUpperState(Glad->ShieldBash);
			}
		}
		else
		{
			ChangeLowerState(Glad->Dodge);
		}
	}
}
