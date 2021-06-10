// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurretClass.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class USceneComponent;
class AProjectile;
class UHealthComponent;
class UParticleSystem;
class USoundBase;

UCLASS()
class DUNGEONESCAPE_API ATurretClass : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurretClass();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Components
	UPROPERTY(VisibleAnywhere, Category = "Turret")
	UCapsuleComponent* CapsuleComponent = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Turret")
	UStaticMeshComponent* TurretBody = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Turret")
	UStaticMeshComponent* TurretHead = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Turret")
	USceneComponent* ProjectileSpawnPoint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	UHealthComponent* HealthComponent;
	
	// Variables
	FTimerHandle FireRateHandle;
	ACharacter* PlayerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "ture"))
	float FireRange = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "ture"))
	float FireRate = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "ture"))
	TSubclassOf<AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Effect", meta = (AllowPrivateAccess = "meta"))
	UParticleSystem* DestroyParticle;
	UPROPERTY(EditAnywhere, Category = "Effect", meta = (AllowPrivateAccess = "meta"))
	USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category = "Effect", meta = (AllowPrivateAccess = "meta"))
	TSubclassOf<UMatineeCameraShake> CameraShake;

	// Functions
	void RotateTurretHead(FVector LookAtTarget);
	void Fire();
	void TurretDestroy();
};
