// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "GladiatorState.h"
#include "UpperBodyState.h"
#include "LowerBodyState.h"
#include "Gladiator.h"


// Sets default values for this component's properties
UGladiatorState::UGladiatorState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	//grab reference to the owner of the actor component and cast it as a Gladiator*, save it to Owner Member variable
	Owner = (AGladiator*)GetOwner();
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

void UGladiatorState::TickState(float DeltaTime)
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

void UGladiatorState::ChangeUpperState(UUpperBodyState* newState)
{
	if (newState->bCanUse)
	{
		Owner->CurrentUpperState->OnStopState();
		Owner->PreviousUpperState = Owner->CurrentUpperState;
		Owner->CurrentUpperState = newState;
		Owner->CurrentUpperState->OnBeginState();
	}
}

void UGladiatorState::ChangeLowerState(ULowerBodyState* newState)
{
	if (newState->bCanUse)
	{
		Owner->CurrentLowerState->OnStopState();
		Owner->PreviousLowerState = Owner->CurrentLowerState;
		Owner->CurrentLowerState = newState;
		Owner->CurrentLowerState->OnBeginState();
	}
}

