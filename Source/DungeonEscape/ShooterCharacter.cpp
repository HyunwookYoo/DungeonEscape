// Fill out your copyright notice in the Description page of Project Settings.
#include "ShooterCharacter.h"

#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Gun.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/MovementComponent.h"
#include "MakeOpen.h"
#include "GameFramework/Actor.h"
#include "DungeonEscapeGameModeBase.h"


#define OUT

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon_Socket"));
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Interaction);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

//float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
//{
//	float DamageToApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
//	float CurrentHealth = HealthComponent->GetHealth();
//
//	DamageToApplied = FMath::Min(CurrentHealth, DamageToApplied);
//
//	CurrentHealth -= DamageToApplied;
//
//	HealthComponent->SetHealth(CurrentHealth);
//
//	UE_LOG(LogTemp, Warning, TEXT("Health Remain: %f"), CurrentHealth);
//
//	return DamageToApplied;
//}

void AShooterCharacter::MoveForward(float Axis)
{
	AddMovementInput(GetActorForwardVector() * Axis);
}

void AShooterCharacter::MoveRight(float Axis)
{
	AddMovementInput(GetActorRightVector() * Axis);
}

void AShooterCharacter::Interaction()
{
	FHitResult Hit;
	GetFirstPhysicsBodyInReach(OUT Hit);

	AActor* HitActor = Hit.GetActor();
	if (HitActor == nullptr) return;

	if (HitActor->ActorHasTag(TEXT("Scanner1")))
	{
		UMakeOpen* MakeOpen = HitActor->FindComponentByClass<UMakeOpen>();
		if (MakeOpen != nullptr)
		{
			MakeOpen->bActivate = true;
		}
	}
}

FHitResult AShooterCharacter::GetFirstPhysicsBodyInReach(FHitResult& Hit) const
{
	FCollisionQueryParams TraceParam(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType
	(
		Hit,
		GetPlayerWorldPosition().Location,
		GetPlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		TraceParam
	);

	DrawDebugLine
	(
		GetWorld(),
		GetPlayerWorldPosition().Location,
		GetPlayerReach(),
		FColor::Red,
		true
	);

	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *(Hit.GetActor()->GetName()));
	}

	return FHitResult();
}

FVector AShooterCharacter::GetPlayerReach() const
{
	return GetPlayerWorldPosition().Location + (GetPlayerWorldPosition().Rotation.Vector() * Reach);
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}

PlayerViewPoint AShooterCharacter::GetPlayerWorldPosition() const
{
	PlayerViewPoint PlayerViewPoint;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPoint.Location, PlayerViewPoint.Rotation);

	return PlayerViewPoint;
}

