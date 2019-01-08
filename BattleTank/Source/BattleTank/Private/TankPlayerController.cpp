// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"




void ATankPlayerController::BeginPlay(){
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    
    if(!ControlledTank){
        UE_LOG(LogTemp,Warning,TEXT("Not possesing a tank"));
    }
    
    else{
        UE_LOG(LogTemp,Warning,TEXT("PlayerController Possesing: %s"), *(ControlledTank->GetName()));
    }
}


//Tick
void ATankPlayerController::Tick(float DeltaTime){
    //Super
    Super::Tick(DeltaTime);
    
    //aim towards crosshairs
    AimTowardsCrosshair();
    
    //UE_LOG(LogTemp,Warning, TEXT("Tick tock goes the clock"));
}


ATank* ATankPlayerController::GetControlledTank() const{
   return Cast<ATank> (GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair(){
    if (!GetControlledTank()){return;}
    
    FVector OutHitLocation; // Out parameter
    if(GetSightRayHitLocation(OutHitLocation)){
    
        GetControlledTank()->AimAt(OutHitLocation);
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
        //Line-Trace along that look direction and see what we hit (up to max range)
             //UE_LOG(LogTemp, Warning, TEXT("Look Direction: %S"), *LookDirection.ToString());
        GetLookVectorHitLocation(LookDirection, OutHitLocation);
    }
    

    return true;
}

       
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const{
    FVector CameraWorldLocation; //To be discarded
    
   return DeprojectScreenPositionToWorld(ScreenLocation.X,ScreenLocation.Y,CameraWorldLocation,LookDirection);
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager ->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    
    if(GetWorld()->LineTraceSingleByChannel(HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility)){

        OutHitLocation = HitResult.Location;
        return true;
    }
    else {
        OutHitLocation = FVector(0);
        return false;
    }
};

