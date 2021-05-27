// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurretClass.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class USceneComponent;
class AProjectile;

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
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent = nullptr;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretBody = nullptr;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretHead = nullptr;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPoint = nullptr;
	
	// Variables
	FTimerHandle FireRateHandle;
	ACharacter* PlayerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "ture"))
	float FireRange = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "ture"))
	float FireRate = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "ture"))
	TSubclassOf<AProjectile> ProjectileClass;

	// Functions
	void RotateTurretHead(FVector LookAtTarget);
	void Fire();
};
