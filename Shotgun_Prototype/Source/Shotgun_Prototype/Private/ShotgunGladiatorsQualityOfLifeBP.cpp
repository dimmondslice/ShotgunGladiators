// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "ShotgunGladiatorsQualityOfLifeBP.h"

/*
UShotgunGladiatorsQualityOfLifeBP::UShotgunGladiatorsQualityOfLifeBP(const class FPostConstructInitializeProperties& PCIP)
    : Super(PCIP)
{
    
}
*/


FPlane UShotgunGladiatorsQualityOfLifeBP::MakeFPlaneNormAndLoc(FVector InBase, FVector InNormal)
{
    return FPlane(InBase, InNormal);
}

float UShotgunGladiatorsQualityOfLifeBP::PlaneDotProduct(FPlane plane, FVector point)
{
    return plane.PlaneDot(point);
}
