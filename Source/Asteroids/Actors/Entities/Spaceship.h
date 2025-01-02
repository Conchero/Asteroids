// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Entities/Entity.h"
#include "Spaceship.generated.h"

/**
 *
 */
struct FInputActionValue;

UCLASS()
class ASTEROIDS_API ASpaceship : public AEntity
{
	GENERATED_BODY()

public:
	ASpaceship();

	UFUNCTION(BlueprintImplementableEvent)
	void SetUIHealth();
	UFUNCTION(BlueprintImplementableEvent)
	void SetUIGameOver(bool show);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsDead() { return b_dead; };

	UFUNCTION(BlueprintCallable)
	void Revive();

	virtual void Death() override;

	virtual void OnHealthChange() override;
	virtual void OnCanTakeDamageRestored() override;

	void SetScore(int _s) { score = _s; };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetScore() { return score; };


	UFUNCTION(BlueprintCallable, BlueprintPure)
	class UShieldComponent* GetShieldComponent() { return shieldComponent; };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class UShootComponent* GetShootComponent() { return shootComponent; };

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

	int score = 0;
	UPROPERTY(EditAnywhere)
	class UTeleportationComponent* tpComponent;
	UPROPERTY(EditAnywhere)
	class UShootComponent* shootComponent;

private:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* shieldMesh;
	class UShieldComponent* shieldComponent;


	void Move(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void StopShoot();

	void ActivateShield();
	void StopShield();


	bool b_canRevive;
	UPROPERTY(EditAnywhere)
	float timerToReviveValue = 1;
	float timerToRevive;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShieldAction;

	class UMaterialInstanceDynamic* spaceshipDynMaterial;
};
