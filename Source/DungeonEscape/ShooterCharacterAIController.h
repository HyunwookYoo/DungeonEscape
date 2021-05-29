// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterCharacterAIController.generated.h"

class UBehaviorTree;

UCLASS()
class DUNGEONESCAPE_API AShooterCharacterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AShooterCharacterAIController();

protected:
	virtual void BeginPlay() override;

private:
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior = nullptr;
};
