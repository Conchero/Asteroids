// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GetDistanceFromActor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UGetDistanceFromActor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGetDistanceFromActor();

	void SetTrackedActor(class AActor* _trackedActor) { actorToTrack = _trackedActor; };

	class AActor* GetActorToTrack() { return actorToTrack; };

	FVector GetDistanceFromActor() {return distanceFromActor;};

	FVector CalculateDistanceFromActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class AActor* actorToTrack;

	class AActor* parentActor;

	FVector distanceFromActor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
