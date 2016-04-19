// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "GladiatorAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories=AnimInstance, BlueprintType)
class SHOTGUN_PROTOTYPE_API UGladiatorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
//SETUP
public:

    APawn* owningPawn;
    UWorld* world;

    virtual void NativeInitializeAnimation() override;
	
    virtual void NativeUpdateAnimation(float DeltaTimeX) override;


//IK FUNCTIONS
public:

    UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "IK|FootTrace")
    void FootTrace(USkeletalMeshComponent* mesh, FVector rootPos, FVector ikTraceStartPos, FVector ikTraceEndPos, FVector footAnkeOffset, ECollisionChannel traceChannel, TArray<AActor*> ignoredActors,
                   bool& hit, FVector& hitLocation, float& hipOffset, FRotator& footRotation, FVector& hitNormal);
	
};
