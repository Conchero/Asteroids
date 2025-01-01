// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

	// Sets default values for this component's properties
public:	

	virtual void OnFire(bool _b, int _direction = 0);

	void SetNbShot(int _nb) {nbShot = _nb;};

	int GetNbShot() {return nbShot;};

	TSubclassOf<class AProjectile> GetProjectileSubClass() {return projectile;};

protected:

	UShootComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> projectile;


	float baseFireRate = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float maxFireRate = 0.15f;


	UPROPERTY(EditAnywhere)
	float fireRateValue = 0.5f;
	float fireRate = fireRateValue;
	int shootDirection = 0;

	int nbShot = 1;

	bool b_firing = false;
	virtual void FireManagement(float _dt);
	virtual void Fire(float speed = -1);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetFireRate(float _v);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentFireRate() {return fireRateValue;};
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetBaseFireRate() {return baseFireRate;};

};
