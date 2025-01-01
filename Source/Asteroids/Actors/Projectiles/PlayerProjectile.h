// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectiles/Projectile.h"
#include "PlayerProjectile.generated.h"

/**
 *
 */
UCLASS()
class ASTEROIDS_API APlayerProjectile : public AProjectile
{
	GENERATED_BODY()


	APlayerProjectile();

protected:

	virtual void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


};
