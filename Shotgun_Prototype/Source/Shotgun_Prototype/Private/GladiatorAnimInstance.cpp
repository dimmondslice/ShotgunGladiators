// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "GladiatorAnimInstance.h"

void UGladiatorAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    //OBTAIN THE OWNING PAWN
    OwningPawn = TryGetPawnOwner();
}

void UGladiatorAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
    Super::NativeUpdateAnimation(DeltaTimeX);

    //DO NOT ADVANCE IF WE DON'T HAVE AN OWNING PAWN
    if (!OwningPawn) { return; }

}
