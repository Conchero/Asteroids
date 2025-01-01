// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectiles/Projectile.h"
#include "Asteroid.generated.h"

/**
 *
 */
UCLASS()
class ASTEROIDS_API AAsteroid : public AProjectile
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float minSpeed = 200;
	UPROPERTY(EditAnywhere)
	float maxSpeed = 700;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAsteroid> asteroidSplit;

	UPROPERTY(EditAnywhere)
	int nbSplit = 0;



	virtual void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:

	void Death();

};
