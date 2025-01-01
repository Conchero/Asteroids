// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Entities/Entity.h"
#include "EnemyEntity.generated.h"

/**
 *
 */
UCLASS()
class ASTEROIDS_API AEnemyEntity : public AEntity
{
	GENERATED_BODY()

public:

	int GetScoreValue() { return scoreValue; };

	int GetDamage() { return damage; };

protected:

	UPROPERTY(EditAnywhere)
	int scoreValue = 100;
	UPROPERTY(EditAnywhere)
	int damage = 1;

	virtual void Death() override;

	UFUNCTION()
	virtual void OnTouchBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

};
