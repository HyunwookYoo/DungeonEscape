// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

AShooterCharacterAIController::AShooterCharacterAIController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AShooterCharacterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}
