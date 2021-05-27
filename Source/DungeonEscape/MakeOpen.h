// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MakeOpen.generated.h"

class AGate;
class UDoorOpen;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UMakeOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMakeOpen();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool bActivate;
	
private:

	UPROPERTY(EditAnywhere)
	AGate* Gate = nullptr;

	UPROPERTY()
	TSubclassOf<UDoorOpen> DoorOpen;
};
