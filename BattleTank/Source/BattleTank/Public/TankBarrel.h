// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

//forward Declaration
class ATank;

UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
    
    //Values between -1 and 1
    void Elevate(float RelativeSpeed);
    
private:
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxDegreesPerSecond = 20; //TODO find sensible default
    
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxElevationDegrees = 40;
    
    UPROPERTY(EditAnywhere, Category = Setup)
    float MinElevationDegrees = 0;
};
