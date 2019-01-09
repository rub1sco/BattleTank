// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
    
    
    //move barrel the right amount this frame
    
    //given a max elevation speed, and frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld() -> DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    
    auto ClampedElevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    
    SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
    
}



