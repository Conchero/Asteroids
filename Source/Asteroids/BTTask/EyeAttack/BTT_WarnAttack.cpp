// Fill out your copyright notice in the Description page of Project Settings.


#include "../../BTTask/EyeAttack/BTT_WarnAttack.h"
#include "AIController.h"
#include "../../Actors/Entities/Boss.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

UBTT_WarnAttack::UBTT_WarnAttack()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;
	NodeName = "Warn Attack";
}

EBTNodeResult::Type UBTT_WarnAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	if (OwnerComp.GetAIOwner()->GetPawn<ABoss>())
	{
		FBTWarnAttack* myMemory = reinterpret_cast<FBTWarnAttack*>(NodeMemory);
		myMemory->boss = OwnerComp.GetAIOwner()->GetPawn<ABoss>();

		if (myMemory->boss)
		{
			myMemory->boss->GetEyeBeamMaterial()->SetScalarParameterValue("Opacity",0.f);
			myMemory->boss->GetEyeBeamMaterial()->SetVectorParameterValue("Color", FColor::Red);
			myMemory->boss->GetEyeBeamMesh()->SetHiddenInGame(false);

			float clampedTrueTimerToWarn = FMath::Clamp(timerToWarn- (1 - (myMemory->boss->GetGlobalHealthPercent()/100)),timerToWarn/2,timerToWarn);

			//quotient to reach given value in a certain time
			myMemory->deltaProgress = maxOpacity / timerToWarn;

			return EBTNodeResult::InProgress;
		}
	}

	return EBTNodeResult::Failed;
}

uint16 UBTT_WarnAttack::GetInstanceMemorySize() const
{
	return sizeof(FBTWarnAttack);

}

void UBTT_WarnAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	if (!OwnerComp.GetAIOwner())
	{
		return;
	}
	FBTWarnAttack* myMemory = reinterpret_cast<FBTWarnAttack*>(NodeMemory);

	if (myMemory->boss)
	{
		//if killed while attacking abort task
		if (myMemory->boss->GetIsDead())
		{
			FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		}
		
		if (myMemory->boss->GetEyeBeamMaterial()->K2_GetScalarParameterValue("Opacity") < maxOpacity)
		{
			myMemory->boss->GetEyeBeamMaterial()->SetScalarParameterValue("Opacity", myMemory->boss->GetEyeBeamMaterial()->K2_GetScalarParameterValue("Opacity") + (myMemory->deltaProgress*DeltaSeconds));
		}
		else
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}


}
