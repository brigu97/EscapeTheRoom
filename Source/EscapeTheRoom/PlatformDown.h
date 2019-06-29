// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "PlatformDown.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API UPlatformDown : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlatformDown();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetTotalMassOnPressurePlate();

private:
	
	void PlatformDown();
	void PlatformUp();

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
		
	UPROPERTY(EditAnywhere)
	float PlatformDelay = 10.0f;

	float LastPlatformDownTime;

	AActor* Owner = nullptr;
};
