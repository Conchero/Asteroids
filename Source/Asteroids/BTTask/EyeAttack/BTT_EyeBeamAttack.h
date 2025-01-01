// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_EyeBeamAttack.generated.h"


struct FBTEyeBeamAttack
{
	class ABoss* boss;
	float deltaProgress;
	float timerToAttack;
};
/**
 *
 */
UCLASS()
class ASTEROIDS_API UBTT_EyeBeamAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_EyeBeamAttack();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual uint16 GetInstanceMemorySize() const override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float timerToAttackValue = 1.f;

};
