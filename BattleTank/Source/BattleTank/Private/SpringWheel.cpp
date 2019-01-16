// Fill out your copyright notice in the Description page of Project Settings.

#include "SpringWheel.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"


// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
    SetRootComponent(MassWheelConstraint);
    
    Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
    Axle -> SetupAttachment(MassWheelConstraint);
    
    Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
    Wheel -> SetupAttachment(Axle);
    
    AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
    AxleWheelConstraint -> SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();
    
}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    SetupConstraint();
}


void ASpringWheel::SetupConstraint()
{
    if (!GetAttachParentActor()){return;}
    
        UPrimitiveComponent* BodyRoot =  Cast<UPrimitiveComponent>(GetAttachParentActor() -> GetRootComponent());
        if(!BodyRoot){return;}
        MassWheelConstraint -> SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
        AxleWheelConstraint -> SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
    
}

void ASpringWheel::AddDrivingForce(float ForceMagnitude)
{
    Wheel -> AddForce(Axle-> GetForwardVector() * ForceMagnitude);
}
