// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arena.generated.h"

UCLASS()
class ASTEROIDS_API AArena : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArena();

	UFUNCTION(BlueprintCallable)
	int GetArenaWidth() { return width; };
	UFUNCTION(BlueprintCallable)
	int GetArenaHeight() { return height; };

	void SpawnReward(TSubclassOf<class ARewardItem> _ri);

	void SpawnBoss(TSubclassOf<class ABoss> _b);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnEnemyManagement(float _dt);

	UPROPERTY(EditAnywhere)
	int width;
	UPROPERTY(EditAnywhere)
	int height;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AEntity>> typeOfAsteroidArray;

	float timerBeforeSpawnEnemyValue = 2.f;
	float timerBeforeSpawnEnemy = timerBeforeSpawnEnemyValue;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditInstanceOnly)
	float heightBossSpawn = 100;
};
