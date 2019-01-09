// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    
    UTankAimingComponent* TankAimingComponent = nullptr;
    
	// Sets default values for this component's properties
	UTankAimingComponent();
    
    //TODO add SetTurretReference
    void AimAt(FVector OutHitLocation, float LaunchSpeed);
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    void SetTurretReference(UTankTurret* TurretToSet);
	
    
private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    void MoveBarrelTowards(FVector AimDirection);
    
};
