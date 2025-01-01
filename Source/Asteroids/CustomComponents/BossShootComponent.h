// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CustomComponents/ShootComponent.h"
#include "BossShootComponent.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API UBossShootComponent : public UShootComponent
{
	GENERATED_BODY()
	

	public:

	virtual void OnFire(bool _b, int _direction = 0) override;

	void SingleShoot();


	protected: 
	
	UBossShootComponent();

	UPROPERTY(EditAnywhere)
	int shotFromCannonDistance = 30;

	virtual void Fire(float speed = -1) override;
};
