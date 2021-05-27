// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class UParticleSystem;
class USoundBase;

UCLASS()
class DUNGEONESCAPE_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* GunMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleEffect = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* OnHitParticle = nullptr;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound = nullptr;

	UPROPERTY(EditAnywhere)
	USoundBase* OnHitSound = nullptr;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;
};
