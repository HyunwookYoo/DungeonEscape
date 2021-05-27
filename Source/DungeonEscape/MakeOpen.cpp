// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeOpen.h"

#include "DoorOpen.h"
#include "Gate.h"

// Sets default values for this component's properties
UMakeOpen::UMakeOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bActivate = false;
}

// Called every frame
void UMakeOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Gate == nullptr) return;

	if (bActivate)
	{
		Gate->FindComponentByClass<UDoorOpen>()->Open();
		bActivate = false;
	}
}


