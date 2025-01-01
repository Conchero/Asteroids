// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RewardItem.generated.h"

UCLASS()
class ASTEROIDS_API ARewardItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARewardItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Effect(class ASpaceship* player);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* collider;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
