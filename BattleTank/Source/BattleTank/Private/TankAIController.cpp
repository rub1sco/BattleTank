// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
}


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    auto PlayerTank = GetWorld() -> GetFirstPlayerController() -> GetPawn();
    auto ControlledTank = GetPawn();
    
    if(ensure(PlayerTank)){
        
        //Move towards player
        MoveToActor(PlayerTank, AcceptedRadius);
        
        
        //aim towards player
        auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
        AimingComponent->AimAt(PlayerTank->GetActorLocation());
        
        
        //Fire if ready
        if (AimingComponent->GetFiringState() == EFiringState::Locked)
        {
        AimingComponent->Fire(); //TODO limit firing rate
        }
    }
    
};

