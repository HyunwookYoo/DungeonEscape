// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpen.h"

#include "Math/UnrealMathUtility.h"


// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();

	CurrentPosition = GetOwner()->GetActorLocation();
	OpenYPosition += CurrentPosition.Y;
	OpenZPosition += CurrentPosition.Z;
}



// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsOpen)
	{
		OpenDoor(DeltaTime);
	}
}

void UDoorOpen::OpenDoor(float DeltaTime)
{
	CurrentPosition.Y = FMath::Lerp(CurrentPosition.Y, OpenYPosition, DoorOpenSpeed * DeltaTime);
	CurrentPosition.Z = FMath::Lerp(CurrentPosition.Z, OpenZPosition, DoorOpenSpeed * DeltaTime);

	GetOwner()->SetActorLocation(CurrentPosition);
}

void UDoorOpen::Open()
{
	bIsOpen = true;
}

