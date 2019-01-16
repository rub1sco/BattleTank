// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "SpringWheel.h"
#include "SpawnPoint.h"
#include "Components/SceneComponent.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
//    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

//void UTankTrack::BeginPlay()
//{
//
//    Super::BeginPlay();
////    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
//
//}

//void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//
//    //Drive tracks
//    DriveTrack();
//
//    //Apply Sideways Force
//    ApplySidewaysForce();
//
//    //reset throttle
//   CurrentThrottle = 0;
//
//}


//void UTankTrack::ApplySidewaysForce() {
//    auto SlipSpeed = FVector::DotProduct(GetRightVector(),GetComponentVelocity());
//
//    //work out required acceleration to correct
//    auto DeltaTime = GetWorld() -> GetDeltaSeconds();
//    auto AccelerationCorrection = -SlipSpeed / DeltaTime * GetRightVector();
//
//    //Calculate and apply sideways force (F = m a)
//    auto TankRoot = Cast<UStaticMeshComponent> (GetOwner()-> GetRootComponent());
//    auto ForceCorrection = (TankRoot->GetMass() * AccelerationCorrection);  //Divides by two because two tracks
//    TankRoot->AddForce(ForceCorrection);
//}


void UTankTrack::SetThrottle(float Throttle)
{
    float CurrentThrottle = FMath::Clamp<float>(Throttle, -1,1);
    DriveTrack(CurrentThrottle);

}


void UTankTrack::DriveTrack(float CurrentThrottle)
{
    auto ForceApplied =  CurrentThrottle * TrackMaxDrivingForce;
    auto Wheels = GetWheels();
    auto ForcePerWheel = ForceApplied / Wheels.Num();
    for (ASpringWheel* Wheel : Wheels)
    {
        Wheel -> AddDrivingForce(ForcePerWheel);
    }
}

TArray<class ASpringWheel*> UTankTrack::GetWheels() const
{
    TArray<ASpringWheel*> ResultArray;
    TArray<USceneComponent*> Children;
    GetChildrenComponents(true,Children);
    for (USceneComponent* Child : Children)
    {
        auto SpawnPointChild = Cast<USpawnPoint>(Child);
        
        if(!SpawnPointChild){continue;}
        
        AActor* SpawnedChild = SpawnPointChild -> GetSpawnedActor();
        auto SpringWheel = Cast<ASpringWheel>(SpawnedChild);
        if(!SpringWheel) {continue;}
        
        ResultArray.Add(SpringWheel);
    }
    return ResultArray;
}
