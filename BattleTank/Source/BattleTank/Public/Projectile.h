// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"



class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
    
    // Sets default values for this actor's properties
    AProjectile();
    void LaunchProjectile(float Speed);
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    

    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* CollisionMesh = nullptr;
    
    UPROPERTY(EditAnywhere, Category = "Components")
    UParticleSystemComponent* LaunchBlast = nullptr;
    
    UPROPERTY(EditAnywhere, Category = "Components")
    UParticleSystemComponent* ImpactBlast = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    URadialForceComponent* ExplosionForce = nullptr;
    

    
private:
    UProjectileMovementComponent* ProjectileMovement = nullptr;
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    void OnTimerExpire();
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float DestroyDelay = 10;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float ProjectileDamage = 20.f;
    
};
