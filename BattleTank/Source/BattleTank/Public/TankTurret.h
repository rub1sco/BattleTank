// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
class ATank;

UCLASS(meta=(BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
    
public:
    void Rotate(float RelativeSpeed);
    
    
private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxDegreesPerSecond = 10; //TODO find sensible default
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxRotateDegrees = 360;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MinRotateDegrees = -360;
};
