// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpringWheel.generated.h"

class USphereComponent;
class UPhysicsConstraintComponent;


UCLASS()
class BATTLETANK_API ASpringWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void AddDrivingForce(float ForceMagnitude);
    
private:
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* Wheel = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPhysicsConstraintComponent* MassWheelConstraint = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* Axle = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
    
    void SetupConstraint();
};
