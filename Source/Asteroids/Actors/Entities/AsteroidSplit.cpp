// Fill out your copyright notice in the Description page of Project Settings.


#include "../Entities/AsteroidSplit.h"

void AAsteroidSplit::SetSpeedAndDirection()
{
	if (parentActor)
	{
		FVector distanceFromParent = GetActorLocation() - parentActor->GetActorLocation();
		velocity = FVector2D(distanceFromParent.X,distanceFromParent.Y);
		speed = FMath::RandRange(minSpeed,maxSpeed);
	}
	else
	{
		// here to make sure it has a speed and direction
		Super::SetSpeedAndDirection();
	}
}

