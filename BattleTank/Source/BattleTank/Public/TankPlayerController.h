// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

//class UTankAimingComponent;
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
    
private:
    ATank* GetControlledTank() const;
    
    // Called every frame
    void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;
    //moves the barrel to hit where crosshair aims.
    void AimTowardsCrosshair();
    
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
    
    UPROPERTY(EditAnywhere)
    float CrosshairXLocation = 0.5;
    UPROPERTY(EditAnywhere)
    float CrosshairYLocation = 0.333;
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 100000;
    
    
};
