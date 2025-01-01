// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_CannonAttack.generated.h"



struct FBTCannonAttack
{
	class ABoss* boss;
	float timerToShoot;
	float timerBetweenRoundShot;
	float nbShot;
};
/**
 *
 */
UCLASS()
class ASTEROIDS_API UBTT_CannonAttack : public UBTTaskNode
{
	GENERATED_BODY()


	UBTT_CannonAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual uint16 GetInstanceMemorySize() const override;


	UPROPERTY(EditAnywhere)
	float timerToShootValue = 1.f;

	UPROPERTY(EditAnywhere)
	float timerBetweenShotRoundValue = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float maxNbShoot = 3;

	UPROPERTY(EditAnywhere)
	float cannonFireRate;

	UPROPERTY(EditAnywhere)
	float bulletSpeed;
};
