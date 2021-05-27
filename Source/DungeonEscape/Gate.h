// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gate.generated.h"

class UStaticMeshComponent;

UCLASS()
class DUNGEONESCAPE_API AGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGate();

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh = nullptr;


};
