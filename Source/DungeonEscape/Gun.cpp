// Fill out your copyright notice in the Description page of Project Settings.
#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "ShooterCharacter.h"

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
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(ParticleEffect, GunMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;

	if (GunTrace(Hit, ShotDirection))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OnHitParticle, Hit.Location, ShotDirection.Rotation());

		FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* Controller = GetOwnerController();
	if (!ensure(Controller != nullptr)) return false;

	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	Controller->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);
	FVector End = PlayerViewpointLocation + (PlayerViewpointRotation.Vector() * MaxRange);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	ShotDirection = -PlayerViewpointRotation.Vector();

	DrawDebugLine(GetWorld(), PlayerViewpointLocation, End, FColor::Red, true);

	return GetWorld()->LineTraceSingleByChannel(Hit, PlayerViewpointLocation, End, ECollisionChannel::ECC_GameTraceChannel2,Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!ensure(OwnerPawn != nullptr)) return nullptr;

	return OwnerPawn->GetController();
}


