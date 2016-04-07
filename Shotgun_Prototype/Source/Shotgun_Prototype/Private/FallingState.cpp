// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "FallingState.h"

void UFallingState::TickState(float DeltaTime)
{
	
}

void UFallingState::ProcessInput(float DeltaTime)
{
	float xSpeed = Glad->MoveForwardAxis;
	float ySpeed = Glad->MoveRightAxis;
	MoveDirection(xSpeed, ySpeed);
}
