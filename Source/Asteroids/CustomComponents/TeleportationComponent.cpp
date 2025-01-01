// Fill out your copyright notice in the Description page of Project Settings.


#include "../CustomComponents/TeleportationComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UTeleportationComponent::UTeleportationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


void UTeleportationComponent::SetLimits(int _minW, int _maxW, int _minH, int _maxH)
{
	minWidth = _minW;
	maxWidth = _maxW;
	minHeight = _minH;
	maxHeight = _maxH;
}

// Called when the game starts
void UTeleportationComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UTeleportationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (parentActor && actorToTrack)
	{
		FVector distanceFromCenter = CalculateDistanceFromActor();
		FVector tpLocation = FVector::ZeroVector;

		if (distanceFromCenter.X > maxWidth)
		{
			tpLocation =  FVector(minWidth, parentActor->GetActorLocation().Y, parentActor->GetActorLocation().Z);
			parentActor->SetActorLocation(tpLocation);
		}
		else if (distanceFromCenter.X < minWidth)
		{
			tpLocation = FVector(maxWidth, parentActor->GetActorLocation().Y, parentActor->GetActorLocation().Z);
			parentActor->SetActorLocation(tpLocation);
		}

		if (distanceFromCenter.Y > maxHeight)
		{
			tpLocation = FVector(parentActor->GetActorLocation().X, minHeight, parentActor->GetActorLocation().Z);
			parentActor->SetActorLocation(tpLocation);
		}
		else if (distanceFromCenter.Y < minHeight)
		{
			tpLocation = FVector(parentActor->GetActorLocation().X, maxHeight, parentActor->GetActorLocation().Z);
			parentActor->SetActorLocation(tpLocation);
		}

	}

	// ...
}

