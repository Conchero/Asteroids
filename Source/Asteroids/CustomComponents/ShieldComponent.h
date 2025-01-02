// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShieldComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UShieldComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShieldComponent();

	void ResetShield();

	void SetHealthComponent(class UHealthComponent* _hc) {healthComponent = _hc;};
	void ActivateShield(class UStaticMeshComponent* _sts);
	void DesactivateShield();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	float GetShieldPercent() { return shieldTimer/timerMaxValue;};

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetIsAvailable() {return isAvailable;};

	void SetIsAvailable(bool _b) {isAvailable = _b;};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UHealthComponent* healthComponent;
	class UStaticMeshComponent* shieldMeshToShow;

	bool b_shieldActivated;
	UPROPERTY(EditAnywhere)
	float timerMaxValue = 3.f;
	float shieldTimer;

	bool isAvailable = false;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
