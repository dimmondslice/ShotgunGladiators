// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "GladiatorState.h"


// Sets default values for this component's properties
UGladiatorState::UGladiatorState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGladiatorState::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGladiatorState::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UGladiatorState::TickState(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
}

void UGladiatorState::OnBeginState()
{
}

void UGladiatorState::OnStopState()
{
}

void UGladiatorState::PauseState()
{
}

void UGladiatorState::ChangeUpperState(UGladiatorState * newState)
{
}

void UGladiatorState::ChangeLowerState(UGladiatorState * newState)
{
}

