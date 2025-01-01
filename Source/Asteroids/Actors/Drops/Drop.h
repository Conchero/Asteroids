// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Drop.generated.h"

UCLASS()
class ASTEROIDS_API ADrop : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrop();

	int GetDropChance() { return dropChance; };
protected:
	UPROPERTY(EditAnywhere);
	int dropChance = 100;
public:

};
