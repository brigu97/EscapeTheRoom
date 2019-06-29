// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	///find attached input component
	void InputHandleComponent();

	///find attached physics handle
	void PhysicsHandleComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	UPROPERTY(EditAnywhere)
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	UInputComponent* InputComponent = nullptr;

	//Ray-Cast and Grab what's is in reach
	void Grab();

	//called when grab is released
	void Release();

	///Returns current start of reach line
	FVector GetReachLineStart();

	///Returns current end of reach line
	FVector GetReachLineEnd();

	//Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
};
