// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASTEROIDS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();
	UFUNCTION(BlueprintCallable)
	void RemoveLife(int _nb);
	UFUNCTION(BlueprintCallable)
	void AddLife(int _nb);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetHealth() { return currentHealth; };
	int GetMaxHealth() { return maxHealth; };

	void Death();


	class AEntity* GetParentEntity() ;

	bool GetCanTakeDamage(){return b_canTakeDamage;};

	float GetDamageCooldownTimer() {return noDamageCooldown;};

	void SetInvunerability(bool _b) {b_haveInvunerability = _b;};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class AEntity* parentEntity;

	UPROPERTY(EditAnywhere)
	int maxHealth = 3;
	int currentHealth = maxHealth;


	bool b_haveInvunerability = false;

	bool b_canTakeDamage = true;
	UPROPERTY(EditAnywhere)
	float noDamageCooldownValue = 1.f;
	float noDamageCooldown = noDamageCooldownValue;
	void NoDamageCooldownManagement(float _dt);


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
