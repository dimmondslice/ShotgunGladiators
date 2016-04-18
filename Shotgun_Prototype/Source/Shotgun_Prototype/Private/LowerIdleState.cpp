// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "LowerIdleState.h"
#include "JumpCrouchState.h"
#include "DodgeState.h"
#include "HoldingShieldState.h"
#include "ShieldBashState.h"
#include "WalkingState.h"

void ULowerIdleState::TickState(float DeltaTime)
{
	
}
void ULowerIdleState::ProcessInput(float DeltaTime)
{
	if (Glad->bJumpAction)
	{
		ChangeLowerState(Glad->JumpCrouch);
	}
	else if (Glad->bDodgeAction)
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
			ChangeLowerState(Glad->Dodge);
		}
		else
		{
			ChangeLowerState(Glad->Dodge);
		}
	}
	else if (Glad->MoveForwardAxis != 0 || Glad->MoveRightAxis != 0)
	{
		ChangeLowerState(Glad->Walking);
	}
}