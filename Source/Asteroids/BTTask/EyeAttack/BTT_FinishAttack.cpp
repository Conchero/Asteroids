// Fill out your copyright notice in the Description page of Project Settings.


#include "../../BTTask/EyeAttack/BTT_FinishAttack.h"
#include "AIController.h"
#include "../../Actors/Entities/Boss.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

UBTT_FinishAttack::UBTT_FinishAttack()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;
	NodeName = "Finish Attack";
}

EBTNodeResult::Type UBTT_FinishAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Set eye values back to default 
	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	if (OwnerComp.GetAIOwner()->GetPawn<ABoss>())
	{
		ABoss* boss = OwnerComp.GetAIOwner()->GetPawn<ABoss>();
		boss->ResetEyeBeamMeshAndMaterial();


		UBlackboardComponent* myBlackboard = OwnerComp.GetBlackboardComponent();
		myBlackboard->SetValueAsEnum("BossState", 0);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}