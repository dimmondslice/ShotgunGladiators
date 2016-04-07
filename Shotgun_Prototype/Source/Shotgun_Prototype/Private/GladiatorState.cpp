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
	bWantsInitializeComponent = true;

	//grab reference to the Glad of the actor component and cast it as a Gladiator*, save it to Glad Member variable
	Glad = (AGladiator*)GetOwner();

	//make sure you can use every state by default
	bCanUse = true;
}

// Called when the game starts
void UGladiatorState::BeginPlay()
{
	//make sure you can use every state by default
	bCanUse = true;
}
void UGladiatorState::InitializeComponent(){}

// Called every frame
void UGladiatorState::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

bool UGladiatorState::Get_bCanUse()
{
	return bCanUse;
}

void UGladiatorState::TickState(float DeltaTime){}
void UGladiatorState::ProcessInput(float DeltaTime){}
void UGladiatorState::OnBeginState(){}
void UGladiatorState::OnStopState(){}
void UGladiatorState::PauseState(){}

void UGladiatorState::ChangeUpperState(UUpperBodyState* newState)
{
	if (newState->Get_bCanUse())
	{
		Glad->CurrentUpperState->OnStopState();
		Glad->PreviousUpperState = Glad->CurrentUpperState;
		Glad->PreviousUpperState->TimeSinceStateStarted = 0;
		Glad->CurrentUpperState = newState;
		Glad->CurrentUpperState->OnBeginState();
	}
}

void UGladiatorState::ChangeLowerState(ULowerBodyState* newState)
{
	if (newState->Get_bCanUse())
	{
		Glad->CurrentLowerState->OnStopState();
		Glad->PreviousLowerState = Glad->CurrentLowerState;
		Glad->PreviousLowerState->TimeSinceStateStarted = 0;
		Glad->CurrentLowerState = newState;
		Glad->CurrentLowerState->OnBeginState();
	}
}

void UGladiatorState::MoveDirection(float _xValue, float _yValue)
{
	Glad->AddMovementInput(Glad->GetActorForwardVector(), _xValue);
	Glad->AddMovementInput(Glad->GetActorRightVector(), _yValue);
}