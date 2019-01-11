// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;
    
//protected:
   UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float AcceptedRadius = 80000; //Default radius close to player
    
private:
    
    virtual void Tick(float DeltaTime) override;
    
    
};
