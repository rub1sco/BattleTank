// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

void UTankTurret::Rotate(float RelativeSpeed){
    
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    
    auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld() -> DeltaTimeSeconds;
    auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
    
    auto ClampedRotation = FMath::Clamp(RawNewRotation, MinRotateDegrees, MaxRotateDegrees);
    
    
   SetRelativeRotation(FRotator(0, ClampedRotation, 0));

}


