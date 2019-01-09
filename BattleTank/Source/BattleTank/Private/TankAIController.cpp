// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"



void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
}


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    auto PlayerTank = Cast<ATank>(GetWorld() -> GetFirstPlayerController() -> GetPawn());
    auto GetAITank = Cast<ATank>(GetPawn());
    
    if(PlayerTank){
        //Move towards player
        
        //aim towards player
        GetAITank->AimAt(PlayerTank->GetActorLocation());
        
        
        //Fire if ready
        GetAITank->Fire(); //TODO limit firing rate
    }
    
};

