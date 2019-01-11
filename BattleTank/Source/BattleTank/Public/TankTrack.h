// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 TankTrack is used to set maximum driving force and to apply forces to the tank.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BluePrintCallable, Category = "Input")
    void SetThrottle(float Throttle);
    
    
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 40000000; //F=ma   40 0000 * 10 (1g accel) = 400 000 Newtons of Force
    
    
private:
    UTankTrack();
    virtual void BeginPlay() override;
    void ApplySidewaysForce();
    void DriveTrack();
    float CurrentThrottle = 0;
    
     UFUNCTION()
     void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
   
    
};
