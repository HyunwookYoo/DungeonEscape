// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretClass.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Projectile.h"
#include "HealthComponent.h"

// Sets default values
ATurretClass::ATurretClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	SetRootComponent(CapsuleComponent);

	TurretBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Body"));
	TurretBody->SetupAttachment(CapsuleComponent);

	TurretHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Head"));
	TurretHead->SetupAttachment(TurretBody);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretHead);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ATurretClass::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	GetWorld()->GetTimerManager().SetTimer(FireRateHandle, this, &ATurretClass::Fire, FireRate, true);
}


// Called every frame
void ATurretClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateTurretHead(PlayerCharacter->GetActorLocation());
	if (HealthComponent->IsDead())
	{
		TurretDestroy();
	}
}

void ATurretClass::RotateTurretHead(FVector LookAtTarget)
{
	FVector LookAtTargetCleaned = FVector(LookAtTarget.X, LookAtTarget.Y, TurretHead->GetComponentLocation().Z);
	FVector StartLocation = TurretHead->GetComponentLocation();

	FRotator TurretHeadRotation = FVector(LookAtTargetCleaned - StartLocation).Rotation();
	TurretHead->SetWorldRotation(TurretHeadRotation);
}

void ATurretClass::Fire()
{
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectile* TempProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}

void ATurretClass::TurretDestroy()
{
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(this, DestroyParticle, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(CameraShake);
	Destroy();
}
