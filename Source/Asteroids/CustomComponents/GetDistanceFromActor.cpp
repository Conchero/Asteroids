// Fill out your copyright notice in the Description page of Project Settings.


#include "../CustomComponents/GetDistanceFromActor.h"

// Sets default values for this component's properties
UGetDistanceFromActor::UGetDistanceFromActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGetDistanceFromActor::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		parentActor = GetOwner();
	}
}


// Called every frame
void UGetDistanceFromActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Called when the game starts
FVector UGetDistanceFromActor::CalculateDistanceFromActor()
{
	if (parentActor && actorToTrack)
	{
		distanceFromActor = parentActor->GetActorLocation() - actorToTrack->GetActorLocation();
	}
	return distanceFromActor;
}