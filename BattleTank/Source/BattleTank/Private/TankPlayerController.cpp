// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "Tank.h"




void ATankPlayerController::BeginPlay(){
    Super::BeginPlay();
    
    auto AimingComponent = GetPawn() ->FindComponentByClass<UTankAimingComponent>();
    if(ensure(AimingComponent))
    {
            FoundAimingComponent(AimingComponent);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot find AimingComponent"))
    }
}


//Tick
void ATankPlayerController::Tick(float DeltaTime){
    //Super
    Super::Tick(DeltaTime);
    
    //aim towards crosshairs
    AimTowardsCrosshair();

}


void ATankPlayerController::AimTowardsCrosshair(){
    
    if(!GetPawn()){return;} //if not possesing
    auto AimingComponent = GetPawn() ->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)){return;}
    
    FVector OutHitLocation; // Out parameter
    bool bGotHitLocation = GetSightRayHitLocation(OutHitLocation);
    
    if(bGotHitLocation){
        AimingComponent->AimAt(OutHitLocation);
    }
};


bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const{
    
    //Find the crosshair position
    int32 ViewPortSizeX, ViewPortSizeY;
    
    GetViewportSize(ViewPortSizeX, ViewPortSizeY);
    auto ScreenLocation = FVector2D ((ViewPortSizeX * CrosshairXLocation), (ViewPortSizeY * CrosshairYLocation));
   
    //Deproject screen Position
    FVector LookDirection;
    
    if(GetLookDirection(ScreenLocation,LookDirection)){

       return GetLookVectorHitLocation(LookDirection, OutHitLocation);
    }
    return false ;
}

       
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const{
    FVector CameraWorldLocation; //To be discarded
    
   return DeprojectScreenPositionToWorld(ScreenLocation.X,ScreenLocation.Y,CameraWorldLocation,LookDirection);
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager ->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    
    if(GetWorld()->LineTraceSingleByChannel(HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Camera)){

        OutHitLocation = HitResult.Location;
        return true;
    }
    else {
        OutHitLocation = FVector(0);
        return false;
    }
};



void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if(InPawn)
    {
        auto PossessedTank = Cast <ATank>(InPawn);
        if (!ensure(PossessedTank)){return;}
        
        //Subscribe to tanks death event
        PossessedTank -> OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
    }
}

void ATankPlayerController::OnPossessedTankDeath()
{
    if(!GetPawn()){return;}
    GetPawn() -> DetachFromControllerPendingDestroy();
    
}
