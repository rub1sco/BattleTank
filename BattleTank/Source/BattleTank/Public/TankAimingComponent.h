// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

//enum for aiming state
UENUM()
enum class EFiringState : uint8{Reloading, Aiming, Locked, OutOfAmmo};



class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    
    UTankAimingComponent* TankAimingComponent = nullptr;
    
	// Sets default values for this component's properties
	UTankAimingComponent();
    
    //TODO add SetTurretReference
    void AimAt(FVector OutHitLocation);
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();

    EFiringState GetFiringState() const;
	
    UFUNCTION(BlueprintCallable, Category = "Firing")
    int GetRoundsLeft()const;
    
protected:
    UPROPERTY(BlueprintReadOnly, Category ="State")
    EFiringState FiringState = EFiringState::Reloading;
    
    UFUNCTION(BluePrintCallable, Category = "Setup")
    void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    
    
    
private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    void MoveBarrelTowards(FVector AimDirection);
    bool IsBarrelMoving();
    
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;
    virtual void BeginPlay() override;
    
    
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4000; //TODO Find sensible default.... in m/s
    
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBluePrint;
    
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float ReloadTimeInSeconds = 3;
    
    double LastFireTime = 0;
    
    FVector AimDirection;
    
    int RoundsLeft = 3;
};
