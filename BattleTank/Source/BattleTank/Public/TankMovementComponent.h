// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * Responsible for moving tank tracks
 */

class UTankTrack;

UCLASS(ClassGroup = (Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BluePrintCallable, Category = "Setup")
    void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
    
    UFUNCTION(BluePrintCallable, Category = "Input")
    void IntendMoveForward(float Throw);
    
    UFUNCTION(BluePrintCallable, Category = "Input")
    void IntendTurnRight(float Throw);
    
    UFUNCTION(BluePrintCallable, Category = "Input")
    void IntendTurnLeft(float Throw);
 

    
private:
    UTankTrack* LeftTrack = nullptr;
    UTankTrack* RightTrack = nullptr;
    
    //call from pathfinding logic by AIController
    virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
    
    
};
