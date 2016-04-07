// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Gladiator.h"

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
	//called after the component is created on the actor after the actor is spawned
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

protected:
	//OurStuff=====================================================================================
	UPROPERTY(VisibleAnywhere)
		bool bCanUse;
public:
	UFUNCTION(BlueprintCallable, category = "GladiatorState")
		virtual bool Get_bCanUse();


	//reference to this actor components actor, cast as a Gladiator
	class AGladiator* Glad;
	//number of seconds that have passed since the state started
	float TimeSinceStateStarted;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//State Functions

	/**Tick function for the State, called from the gladiator script*/
	virtual void TickState(float DeltaTime);
	/**Called every frame from Gladiator tick. Check for input here*/
	UFUNCTION(BlueprintCallable, category = "GladiatorState")
	/**Called every frame the state is active, any state logic related to input should be done here*/
	virtual void ProcessInput(float DeltaTime);
	/**Called when the gladiators State changes to this state*/
	virtual void OnBeginState();
	/**Called when the gladiators state changes off of this state*/
	virtual void OnStopState();
	/**Pauses this state so that it's tick is not called, but doesn't change the state*/
	virtual void PauseState();
	/**Changes the current upper body state
	@param newState is the new upperbody state you want to transition to
	*/
	virtual void ChangeUpperState(class UUpperBodyState* newState);
	/**Changes the current lower body state
	@param newState is the new lowerbody state you want to transition to
	*/
	virtual void ChangeLowerState(class ULowerBodyState* newState);

	float FPS60ToSeconds = 0.0166667f;

	void MoveDirection(float _xValue, float _yValue);
};
