// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Runtime/Core/Public/Math/Vector.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
    
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    //Variables
    auto TankForward = GetOwner()-> GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    
    //Calculations
    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention);
    auto LeftThrow = FVector::CrossProduct(AIForwardIntention, TankForward);
    
    
    
    IntendMoveForward(ForwardThrow);
    IntendTurnRight(RightThrow.Z);
    IntendTurnLeft(LeftThrow.Z);
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
    
    if (!ensure(LeftTrack && RightTrack)){return;}
    LeftTrack -> SetThrottle(Throw);
    RightTrack -> SetThrottle(Throw);
    
    //TODO Prevent double speed due to dual controller use
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
    
    if (!ensure(LeftTrack && RightTrack)){return;}
    LeftTrack -> SetThrottle(Throw);
    RightTrack -> SetThrottle(-Throw);

    //TODO Prevent double speed due to dual controller use
}


void UTankMovementComponent::IntendTurnLeft(float Throw)
{
    
    if (!ensure(LeftTrack && RightTrack)){return;}
    LeftTrack -> SetThrottle(-Throw);
    RightTrack -> SetThrottle(Throw);
    

}
