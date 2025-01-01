// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Entities/EnemyEntity.h"
#include "AsteroidEnemy.generated.h"

/**
 *
 */
UCLASS()
class ASTEROIDS_API AAsteroidEnemy : public AEnemyEntity
{
	GENERATED_BODY()


protected:
	AAsteroidEnemy();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Death() override;

	virtual void SetSpeedAndDirection();
	void PositionOverTime(float deltaTime);

	void SortDropObject();

	void AsteroidSplit(class AAsteroidGameMode* _gm);

	UPROPERTY(VisibleAnywhere)
	FVector2D velocity;
	UPROPERTY(VisibleAnywhere)
	float speed;
	UPROPERTY(EditAnywhere)
	float minSpeed = 100;
	UPROPERTY(EditAnywhere)
	float maxSpeed = 300;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAsteroidSplit> asteroidSplit;
	UPROPERTY(EditAnywhere)
	int nbSplit = 0;

	UPROPERTY(EditAnywhere)
	class UDestroyWhenOutOfBounds* distanceComponent;

	UPROPERTY(EditAnywhere)
	int dropChance = 20;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ADrop>> dropObjectArray;
};
