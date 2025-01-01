// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_WarnAttack.generated.h"


struct FBTWarnAttack
{
	class ABoss* boss;
	float deltaProgress;
};

/**
 *
 */
UCLASS()
class ASTEROIDS_API UBTT_WarnAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_WarnAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual uint16 GetInstanceMemorySize() const override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float timerToWarn = 2.f;
	UPROPERTY(EditAnywhere)
	float maxOpacity = 0.3f;

};
