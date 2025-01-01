// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Entities/EnemyEntity.h"
#include "BossCannon.generated.h"

/**
 *
 */
UCLASS()
class ASTEROIDS_API ABossCannon : public AEnemyEntity
{
	GENERATED_BODY()

	ABossCannon();

public:



	virtual void Death() override;
	virtual void OnCanTakeDamageRestored() override;
	
	void SetTranslationSpeed(int _i) { translationSpeed = _i; };

	void SetMovement(bool _b) { isMoving = _b; }

	void SetLimits(TArray<int> _l) { translationLimits = _l; };

	void SetBossParent(class ABoss* _boss) { bossParent = _boss; };

	void SingleShoot();

	TArray<int> GetTranslationLimits() { return translationLimits; };


	bool CheckPlayerCannonRaycast();


	int GetCannonWidth() {return cannonWidth;};

	class UBossShootComponent* GetShootComponent() { return shootComponent;};


	virtual void OnHealthChange() override;

protected:

	class UMaterialInstanceDynamic* cannonDynMaterial;


	class ABoss* bossParent;

	void Move(float _dt);

	UPROPERTY(EditAnywhere)
	int translationSpeed = 300;
	UPROPERTY(EditAnywhere)
	int translationDirection = 1;
	bool isMoving = true;


	TArray<int> translationLimits;

	UPROPERTY(EditAnywhere)
	class UBossShootComponent* shootComponent;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	int cannonWidth = 200;

};
