// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declarations
class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetTurretReference(UTankTurret* TurretToSet);
    
    UFUNCTION(BlueprintCallable, Category = Firing)
    void Fire();
    
    void AimAt(FVector OutHitLocation);
    

    
    
private:
	// Sets default values for this pawn's properties
	ATank();

    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float LaunchSpeed = 4000; //TODO Find sensible default.... in m/s
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBluePrint;
    
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float ReloadTimeInSeconds = 3;
    
    
    
    //Local barrel ref for spawning projectile
    UTankBarrel* Barrel = nullptr;
    
    double LastFireTime = 0;

    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UTankAimingComponent* TankAimingComponent = nullptr;
    
    UPROPERTY(BluePrintReadOnly)
    UTankMovementComponent* TankMovementComponent = nullptr;


};
