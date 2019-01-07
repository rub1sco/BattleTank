// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"



void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    
    auto PlayerTank = GetPlayerTank();
    
    if(!PlayerTank){
        UE_LOG(LogTemp,Warning,TEXT("AI controller can't find player Tank"));
    }
    
    else{
        UE_LOG(LogTemp,Warning,TEXT("AIController found player: %s"), *(PlayerTank->GetName()));
    }
}


void ATankAIController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
    
    if(!GetPlayerTank()){return;}
    
    //Move towards player
    
    //aim towards player
    GetAITank()-> AimAt(GetPlayerTank() ->GetActorLocation());
    
    //Fire if ready
    
    
};


ATank* ATankAIController::GetAITank() const{
    return Cast<ATank> (GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const{
    auto PlayerPawn = GetWorld() -> GetFirstPlayerController() -> GetPawn();
    if (!PlayerPawn){
        return nullptr;
    }
    
    return Cast<ATank> (PlayerPawn);
}
