// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_CheckPlayerWithRaycast.generated.h"


struct FBTCheckPlayerNodeMemory
{
	//0 left cannon, 1 boss Eye, 2 right Cannon
	TArray<int> checkResult;
	int nbCheck;
};

/**
 *
 */
UCLASS()
class ASTEROIDS_API UBTT_CheckPlayerWithRaycast : public UBTTaskNode
{
	GENERATED_BODY()


	UBTT_CheckPlayerWithRaycast();
protected:

	FBlackboardKeySelector BossState;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual uint16 GetInstanceMemorySize() const override;
};
