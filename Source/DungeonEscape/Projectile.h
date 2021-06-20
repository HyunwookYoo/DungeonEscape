// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class USoundBase;
class UBoxComponent;

UCLASS()
class DUNGEONESCAPE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystemComponent* TrailParticleSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ExplodeParticleSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	USoundBase* LaunchSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MovementSpeed = 1000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float Damage = 50.f;

	UPROPERTY(VisibleAnywhere, Category = "Damage")
	TSubclassOf<UDamageType> DamageTypeClass;
};
