// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Entity.generated.h"

UCLASS()
class ASTEROIDS_API AEntity : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEntity();

	class UStaticMeshComponent* GetMesh() { return mesh; };

	virtual void Death();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	class UHealthComponent* GetHealthComponent() { return healthComponent; };

	virtual void OnHealthChange();
	virtual void OnCanTakeDamageRestored();

	bool GetIsDead() { return b_dead; };
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class USceneComponent* container;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxCollider;

	UPROPERTY(EditAnywhere)
	class UHealthComponent* healthComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* MovementComponent;

	bool b_dead = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
