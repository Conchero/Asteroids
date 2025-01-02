// Fill out your copyright notice in the Description page of Project Settings.


#include "../BTTask/BTT_CheckPlayerWithRaycast.h"
#include "AIController.h"
#include "../Actors/Entities/Boss.h"
#include "../Enums/EBossState.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_CheckPlayerWithRaycast::UBTT_CheckPlayerWithRaycast()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;
	NodeName = "Check Player";
}

EBTNodeResult::Type UBTT_CheckPlayerWithRaycast::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}


	if (OwnerComp.GetAIOwner()->GetPawn<ABoss>())
	{
		FBTCheckPlayerNodeMemory* myMemory = reinterpret_cast<FBTCheckPlayerNodeMemory*>(NodeMemory);

		ABoss* boss = OwnerComp.GetAIOwner()->GetPawn<ABoss>();
		if (myMemory->nbCheck <= 20)
		{
			myMemory->nbCheck++;
			return EBTNodeResult::Succeeded;
		}
		else
		{

			int attackIndex = 0;
			if (boss->CheckPlayerPresence() >= 0)
			{
				//if player was in front of an alive part attacks depending on which part was returned
				if (myMemory->checkResult.Num() < 3)
				{
					myMemory->checkResult.SetNum(3);
				}
				myMemory->checkResult[boss->CheckPlayerPresence()]++;
				TArray<int> sortedCheckResult = myMemory->checkResult;
				sortedCheckResult.Sort();
				attackIndex = myMemory->checkResult.Find(sortedCheckResult[sortedCheckResult.Num() - 1]);
				myMemory->checkResult.Empty();
			}
			else
			{
				//if player was not found do a random attack with the alive parts
				if (boss->GetPartsAlive().Num() > 0)
				{
					int randomIndex = FMath::RandRange(0, boss->GetPartsAlive().Num()-1);
					attackIndex = boss->GetPartsAlive()[randomIndex];
				}
			}


			UBlackboardComponent* myBlackboard = OwnerComp.GetBlackboardComponent();
			myBlackboard->SetValueAsEnum("BossState", attackIndex + 1);
			myMemory->nbCheck = 0;
			return EBTNodeResult::Succeeded;
		}


	}

	return EBTNodeResult::Failed;
}

uint16 UBTT_CheckPlayerWithRaycast::GetInstanceMemorySize() const
{
	return sizeof(FBTCheckPlayerNodeMemory);
}
