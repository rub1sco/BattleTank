// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankTurret.h" //
#include "TankBarrel.h"
#include "TankTurret.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet){
    Barrel = BarrelToSet;
    
}


void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet){
    Turret = TurretToSet; //
}


void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed)
{
    //Protecting pointers
    if(!Barrel){return;}
    if (!Turret){return;} //
    
    FVector OutLaunchVelocity(0);
    FVector StartLocation = Barrel-> GetSocketLocation(FName("Projectile"));
    
    //Calculate Out Launch Velocity
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
    (
     this,
     OutLaunchVelocity,
     StartLocation,
     OutHitLocation,
     LaunchSpeed,
     false,
     0,
     0,
     ESuggestProjVelocityTraceOption::DoNotTrace // Paramater must be present to prevent bug
     );
    
    
    
    if(bHaveAimSolution)
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
    //else do nothing
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    //work out distance between current barrel relation and aim direction
    auto BarrelRotation = Barrel-> GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotation;
    
    Barrel -> Elevate(DeltaRotator.Pitch);
    Turret -> Rotate(DeltaRotator.Yaw);
    
}
