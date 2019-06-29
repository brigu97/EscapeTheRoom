// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "PhysicsManipulationMode.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Gameframework/Actor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Gameframework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	//Find the owning actor
	Owner = GetOwner();
	if (!PressurePlate) 
	{ 
		UE_LOG(LogTemp,Warning,TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}

void UOpenDoor::OpenDoor()
{

	//Set the door rotation
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	//closing the door
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PressurePlate) { return; }
	//Poll the Trigger Volume
	//If the ActorThatOpens is in the volume
	if (GetTotalMassOnPressurePlate() > 50.f)//TODO make into parameter
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	//check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}

}

float UOpenDoor::GetTotalMassOnPressurePlate()
{ 
	float TotalMass = 0.f;
	
	// Find all the overlapping actors
	TArray<AActor*> OverLappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverLappingActors);
	// Iterate through them adding their masses
	for (const auto* Actor : OverLappingActors)
	{
		TotalMass = TotalMass + Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}
