// Fill out your copyright notice in the Description page of Project Settings.


#include "../CustomComponents/DestroyWhenOutOfBounds.h"
#include "../Actors/Arena.h"
#include "Kismet/GameplayStatics.h"

void UDestroyWhenOutOfBounds::BeginPlay()
{
	Super::BeginPlay();

	if (UGameplayStatics::GetActorOfClass(GetWorld(), AArena::StaticClass()))
	{
		AArena* arena = Cast<AArena>(UGameplayStatics::GetActorOfClass(GetWorld(), AArena::StaticClass()));
		limits.X = arena->GetArenaWidth() / 2;
		limits.Y = arena->GetArenaHeight()/2;
	}
	

}

void UDestroyWhenOutOfBounds::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FMath::Abs(CalculateDistanceFromActor().X) > limits.X)
	{
		GetOwner()->Destroy();
	}
	else if (FMath::Abs(CalculateDistanceFromActor().Y) > limits.Y)
	{
		GetOwner()->Destroy();
	}


}
