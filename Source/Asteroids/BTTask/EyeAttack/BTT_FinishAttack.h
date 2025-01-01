// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_FinishAttack.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API UBTT_FinishAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_FinishAttack();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
