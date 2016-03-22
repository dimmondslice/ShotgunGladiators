// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShotgunGladiatorsQualityOfLifeBP.generated.h"

/**
 * 
 */
UCLASS()
class SHOTGUN_PROTOTYPE_API UShotgunGladiatorsQualityOfLifeBP : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category="Plane")
    static FPlane MakeFPlaneNormAndLoc(FVector InBase, FVector InNormal);
	
    UFUNCTION(BlueprintCallable, Category="Plane")
    static float PlaneDotProduct(FPlane plane, FVector point);
	
};
