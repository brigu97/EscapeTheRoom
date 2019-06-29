// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformUp.h"
#include "Engine/World.h"
#include "PhysicsManipulationMode.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Gameframework/Actor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UPlatformUp::UPlatformUp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPlatformUp::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();	
}


void UPlatformUp::PlatformDown()
{
	//Set the plateform location
	Owner->SetActorLocation(FVector(-430.f, 2050.f, 2060.f));
}

void UPlatformUp::PlatformUp()
{
	Owner->SetActorLocation(FVector(110.f, 690.f, 2720.f));
}

// Called every frame
void UPlatformUp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PressurePlate) { return; }
	//Poll the Trigger Volume
	//If the ActorThatOpens is in the volume
	if (GetTotalMassOnPressurePlate() > 50.f)//TODO make into parameter
	{
		PlatformDown();
		LastPlatformDownTime = GetWorld()->GetTimeSeconds();
	}

	//check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastPlatformDownTime > PlatformDelay)
	{
		PlatformUp();
	}
}

float UPlatformUp::GetTotalMassOnPressurePlate()
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


