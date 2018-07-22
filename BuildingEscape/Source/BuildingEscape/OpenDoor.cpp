// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (ReturnTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast(); //Open the door
	}
	else {
		OnClose.Broadcast(); //Open the door
	}
}

float UOpenDoor::ReturnTotalMassOfActorsOnPlate()
{
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("No PressurePlate found"));
		return 0.f;
	}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	float TotalMass = 0.f;
	for (auto& Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("mass found: %s"), *Actor->GetName())
	}
	return TotalMass;
}