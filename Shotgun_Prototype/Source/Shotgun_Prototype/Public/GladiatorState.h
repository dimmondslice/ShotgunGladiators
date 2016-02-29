// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GladiatorState.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOTGUN_PROTOTYPE_API UGladiatorState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGladiatorState();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


	//OurStuff=====================================================================================
	UPROPERTY(VisibleAnywhere)
		bool bCanUse;
	//reference to this actor components actor, cast as a Gladiator
	class AGladiator* Owner;


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//State Functions

	/**Tick function for the State, called from the gladiator script*/
	virtual void TickState(float DeltaTime);

	/**Called when the gladiators State changes to this state*/
	virtual void OnBeginState();
	/**Called when the gladiators state changes off of this state*/
	virtual void OnStopState();
	/**Pauses this state so that it's tick is not called, but doesn't change the state*/
	virtual void PauseState();
	/**Changes the current upper body state */
	virtual void ChangeUpperState(class UUpperBodyState* newState);
	/**Changes the current lower body state */
	virtual void ChangeLowerState(class ULowerBodyState* newState);
	
};
