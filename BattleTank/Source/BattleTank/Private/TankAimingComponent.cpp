// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankTurret.h" //
#include "TankBarrel.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"





// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    
    //TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	// ...
}


void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();
    
    //makes first fire load after begin play
    LastFireTime = FPlatformTime::Seconds();
    
}



void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    if (RoundsLeft <= 0)
    {
        FiringState = EFiringState::OutOfAmmo;
    }
    
    //determines if reloaded or now
    else if((FPlatformTime::Seconds()-LastFireTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    }
    
    //handle aiming and locked states
    else if(IsBarrelMoving())
    {
         FiringState = EFiringState::Aiming;
    }
    else
    {
         FiringState = EFiringState::Locked;
    }
}


void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
   
    Barrel = BarrelToSet;
    Turret = TurretToSet;
    
}




void UTankAimingComponent::AimAt(FVector OutHitLocation)
{
    //Protecting pointers
    if(!ensure(Barrel)){return;}
    if (!ensure(Turret)){return;} //
    
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
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
    //else do nothing
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    
    if (!ensure(Barrel) || !ensure(Turret)){return;}
     
    //work out distance between current barrel relation and aim direction
    auto BarrelRotation = Barrel-> GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotation;
    
    Barrel -> Elevate(DeltaRotator.Pitch);
    
    if (FMath::Abs(DeltaRotator.Yaw < 180))
    {
    Turret -> Rotate(DeltaRotator.Yaw);
    }
    else
    {
       Turret -> Rotate(-DeltaRotator.Yaw);
    }
}


EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}

void UTankAimingComponent::Fire()
{
    if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
    {
        if(!ensure(Barrel && ProjectileBluePrint)){return;}
        {
            //Spawn a projectile at socket location
            auto Projectile = GetWorld() -> SpawnActor<AProjectile>(
                ProjectileBluePrint,
                Barrel -> GetSocketLocation(FName("Projectile")),
                Barrel -> GetSocketRotation(FName("Projectile"))
                );

            //Launch Projectile
            Projectile -> LaunchProjectile(LaunchSpeed);
            RoundsLeft--;
            
        }
        
    }
}


bool UTankAimingComponent::IsBarrelMoving()
{
    if(!ensure(Barrel)){return false;}
    
    auto BarrelForward = Barrel-> GetForwardVector();
    
    return !BarrelForward.Equals(AimDirection, 0.01);
}


int UTankAimingComponent::GetRoundsLeft()const
{
    
    return RoundsLeft;
}

