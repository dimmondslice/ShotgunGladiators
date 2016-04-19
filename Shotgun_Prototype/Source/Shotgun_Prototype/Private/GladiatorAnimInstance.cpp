// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun_Prototype.h"
#include "GladiatorAnimInstance.h"

void UGladiatorAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    //OBTAIN THE OWNING PAWN
    owningPawn = TryGetPawnOwner();
    world = GetWorld();
}

void UGladiatorAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
    Super::NativeUpdateAnimation(DeltaTimeX);

    //DO NOT ADVANCE IF WE DON'T HAVE AN OWNING PAWN
    if (!owningPawn) { return; }

}


void UGladiatorAnimInstance::FootTrace(USkeletalMeshComponent* mesh, FVector rootPos, FVector ikTraceStartPos, FVector ikTraceEndPos, FVector footAnkeOffset, ECollisionChannel traceChannel, TArray<AActor*> ignoredActors,
                                       bool& hit, FVector& hitLocation, float& hipOffset, FRotator& footRotation, FVector& hitNormal)
{

    //FCollisionQueryParams(FName(TEXT("IK Foot Trace")), false, ignoredActors);

    FCollisionQueryParams collisionParams;
    collisionParams.AddIgnoredActors(ignoredActors);

    FHitResult hitResult;

    world->LineTraceSingleByChannel(hitResult, ikTraceStartPos, ikTraceEndPos, traceChannel, collisionParams);


    hit = hitResult.bBlockingHit;


    
}