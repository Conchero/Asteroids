// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CustomComponents/GetDistanceFromActor.h"
#include "TeleportationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UTeleportationComponent : public UGetDistanceFromActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTeleportationComponent();



	void SetLimits(int _minW, int _maxW, int _minH, int _maxH);

	int GetMinWidth() { return minWidth; };
	int GetMaxWidth() { return maxWidth; };
	int GetMinHeight() { return minHeight; };
	int GetMaxHeight() {return maxHeight;};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	int maxWidth;
	int minWidth;
	int maxHeight;
	int minHeight;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
