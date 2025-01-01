// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CustomComponents/GetDistanceFromActor.h"
#include "DestroyWhenOutOfBounds.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API UDestroyWhenOutOfBounds : public UGetDistanceFromActor
{
	GENERATED_BODY()
	


	protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FVector2D limits;

};
