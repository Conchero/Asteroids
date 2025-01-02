// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Entities/AsteroidEnemy.h"
#include "AsteroidSplit.generated.h"

/**
 *
 */
UCLASS()
class ASTEROIDS_API AAsteroidSplit : public AAsteroidEnemy
{
	GENERATED_BODY()


public:

 void SetParentActor( class AActor* _actor) { parentActor= _actor;};
 virtual void SetSpeedAndDirection() override;

protected:

	class AActor* parentActor;
};
