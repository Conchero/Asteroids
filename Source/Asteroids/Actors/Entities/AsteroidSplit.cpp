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
		Super::SetSpeedAndDirection();
	}


}

void AAsteroidSplit::BeginPlay()
{
	Super::BeginPlay();


}
