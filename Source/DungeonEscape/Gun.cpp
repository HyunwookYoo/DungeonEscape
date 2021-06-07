// Fill out your copyright notice in the Description page of Project Settings.
#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "ShooterCharacter.h"
#include "Projectile.h"

#define OUT

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(Root);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(Root);

	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPoint"));
	BulletSpawnPoint->SetupAttachment(GunMesh);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();


}

void AGun::PullTrigger()
{
	if (Bullet)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, GunMesh, TEXT("MuzzleFlashSocket"));
		FVector SpawnLocation = BulletSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = BulletSpawnPoint->GetComponentRotation();
		AProjectile* Temp = GetWorld()->SpawnActor<AProjectile>(Bullet, SpawnLocation, SpawnRotation);
		Temp->SetOwner(this);
	}
}


