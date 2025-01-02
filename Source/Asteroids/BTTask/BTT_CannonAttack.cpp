// Fill out your copyright notice in the Description page of Project Settings.


#include "../BTTask/BTT_CannonAttack.h"
#include "AIController.h"
#include "../Actors/Entities/Boss.h"
#include "../CustomComponents/BossShootComponent.h"
#include "../Actors/Entities/BossCannon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Enums/EBossState.h"
#include "../Actors/Entities/BossCannon.h"

UBTT_CannonAttack::UBTT_CannonAttack()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;
	NodeName = "Cannon attack";
}

EBTNodeResult::Type UBTT_CannonAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	if (OwnerComp.GetAIOwner()->GetPawn<ABoss>())
	{
		FBTCannonAttack* myMemory = reinterpret_cast<FBTCannonAttack*>(NodeMemory);
		myMemory->boss = OwnerComp.GetAIOwner()->GetPawn<ABoss>();
		myMemory->timerToShoot = timerToShootValue;
		myMemory->nbShot = 0;
		myMemory->timerBetweenRoundShot = timerBetweenShotRoundValue;
		myMemory->boss->SetMoveCannon(false);


		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;

}

void UBTT_CannonAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	if (!OwnerComp.GetAIOwner())
	{
		return;
	}

	FBTCannonAttack* myMemory = reinterpret_cast<FBTCannonAttack*>(NodeMemory);

	if (myMemory->boss->GetRightCannon()->GetIsDead() && myMemory->boss->GetLeftCannon()->GetIsDead())
	{
		if (myMemory->boss->GetRightCannon() && myMemory->boss->GetRightCannon()->GetShootComponent())
			myMemory->boss->GetRightCannon()->GetShootComponent()->OnFire(false);
		if (myMemory->boss->GetLeftCannon() && myMemory->boss->GetLeftCannon()->GetShootComponent())
			myMemory->boss->GetLeftCannon()->GetShootComponent()->OnFire(false);

		UBlackboardComponent* myBlackboard = OwnerComp.GetBlackboardComponent();
		myBlackboard->SetValueAsEnum("BossState", 0);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}


	//e.g three rounds of shot each lasting for a second 
	if (myMemory->nbShot < maxNbShoot)
	{

		if (myMemory->timerToShoot > 0)
		{
			if (myMemory->boss->GetRightCannon() && myMemory->boss->GetRightCannon()->GetShootComponent())
				myMemory->boss->GetRightCannon()->GetShootComponent()->OnFire(true);
			if (myMemory->boss->GetLeftCannon() && myMemory->boss->GetLeftCannon()->GetShootComponent())
				myMemory->boss->GetLeftCannon()->GetShootComponent()->OnFire(true);

			myMemory->timerToShoot -= DeltaSeconds;
		}
		else if (myMemory->timerBetweenRoundShot > 0)
		{
			myMemory->timerBetweenRoundShot -= DeltaSeconds;

			if (myMemory->boss->GetRightCannon() && myMemory->boss->GetRightCannon()->GetShootComponent())
				myMemory->boss->GetRightCannon()->GetShootComponent()->OnFire(false);
			if (myMemory->boss->GetLeftCannon() && myMemory->boss->GetLeftCannon()->GetShootComponent())
				myMemory->boss->GetLeftCannon()->GetShootComponent()->OnFire(false);
		}
		else
		{
			myMemory->timerBetweenRoundShot = timerBetweenShotRoundValue;
			myMemory->timerToShoot = timerToShootValue;
			myMemory->nbShot++;
		}

	}
	else
	{
		UBlackboardComponent* blackboardComponent = OwnerComp.GetBlackboardComponent();
		if (blackboardComponent)
		{
			blackboardComponent->SetValueAsEnum("BossState", 0);
		}
		myMemory->boss->SetMoveCannon(true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}

uint16 UBTT_CannonAttack::GetInstanceMemorySize() const
{
	return sizeof(FBTCannonAttack);
}
