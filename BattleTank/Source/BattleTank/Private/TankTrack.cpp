// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit); 
}

void UTankTrack::BeginPlay()
{
    
    Super::BeginPlay();
//    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
 
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

    //Drive tracks
    DriveTrack();
    
    //Apply Sideways Force
    ApplySidewaysForce();
    
    //reset throttle
   CurrentThrottle = 0;
    
}


void UTankTrack::ApplySidewaysForce() {
    auto SlipSpeed = FVector::DotProduct(GetRightVector(),GetComponentVelocity());
    
    //work out required acceleration to correct
    auto DeltaTime = GetWorld() -> GetDeltaSeconds();
    auto AccelerationCorrection = -SlipSpeed / DeltaTime * GetRightVector();
    
    //Calculate and apply sideways force (F = m a)
    auto TankRoot = Cast<UStaticMeshComponent> (GetOwner()-> GetRootComponent());
    auto ForceCorrection = (TankRoot->GetMass() * AccelerationCorrection);  //Divides by two because two tracks
    TankRoot->AddForce(ForceCorrection);
}


void UTankTrack::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1,1);

}


void UTankTrack::DriveTrack()
{
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot -> AddForceAtLocation(ForceApplied, ForceLocation);
}
