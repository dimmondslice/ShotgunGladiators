// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpperBodyState.h"
#include "RaiseShieldState.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API URaiseShieldState : public UUpperBodyState
{
	GENERATED_BODY()

		virtual void OnBeginState() override;
	
};
