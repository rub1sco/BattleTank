// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    
    
    //move barrel the right amount this frame
    
    //given a max elevation speed, and frame time
    auto Time = GetWorld() -> GetTimeSeconds();
    
    UE_LOG(LogTemp, Warning, TEXT("%f Barrel Elevate Called at speed %f"), Time, RelativeSpeed);
}



