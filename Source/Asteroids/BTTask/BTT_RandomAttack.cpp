// Fill out your copyright notice in the Description page of Project Settings.


#include "../BTTask/BTT_RandomAttack.h"
#include "AIController.h"
#include "../Actors/Entities/Boss.h"
#include "../CustomComponents/BossShootComponent.h"
#include "../Actors/Entities/BossCannon.h"

UBTT_RandomAttack::UBTT_RandomAttack()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;
	NodeName = "Random Attack";
}

EBTNodeResult::Type UBTT_RandomAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	if (OwnerComp.GetAIOwner()->GetPawn<ABoss>())
	{
		ABoss* boss = OwnerComp.GetAIOwner()->GetPawn<ABoss>();
		int randomNumber = FMath::RandRange(0, 4);

		if (randomNumber < 1)
		{
			if (boss->GetRightCannon() && boss->GetRightCannon()->GetShootComponent())
			boss->GetRightCannon()->SingleShoot();

			if (boss->GetLeftCannon() && boss->GetLeftCannon()->GetShootComponent())
			boss->GetLeftCannon()->SingleShoot();
		}

		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}

}
