// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "ShooterCharacter.generated.h"

class AGun;

struct PlayerViewPoint
{
	FVector Location;
	FRotator Rotation;
};

UCLASS()
class DUNGEONESCAPE_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void Interaction();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	FHitResult GetFirstPhysicsBodyInReach(FHitResult& Hit) const;
	float Reach = 250.f;
	FVector GetPlayerReach() const;
	PlayerViewPoint GetPlayerWorldPosition() const;
};
