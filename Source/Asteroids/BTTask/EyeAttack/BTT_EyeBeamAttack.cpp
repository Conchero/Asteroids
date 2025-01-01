// Fill out your copyright notice in the Description page of Project Settings.


#include "../../BTTask/EyeAttack/BTT_EyeBeamAttack.h"
#include "AIController.h"
#include "../../Actors/Entities/Boss.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
UBTT_EyeBeamAttack::UBTT_EyeBeamAttack()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;
	NodeName = "Eye Beam Attack";
}

EBTNodeResult::Type UBTT_EyeBeamAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	if (OwnerComp.GetAIOwner()->GetPawn<ABoss>())
	{
		FBTEyeBeamAttack* myMemory = reinterpret_cast<FBTEyeBeamAttack*>(NodeMemory);
		myMemory->boss = OwnerComp.GetAIOwner()->GetPawn<ABoss>();

		myMemory->deltaProgress = myMemory->boss->GetEyeBeamMesh()->GetRelativeScale3D().X / timerToAttackValue;
		myMemory->timerToAttack = timerToAttackValue;

		FVector initScale = FVector(0, myMemory->boss->GetEyeBeamMesh()->GetRelativeScale3D().Y, myMemory->boss->GetEyeBeamMesh()->GetRelativeScale3D().Z);
		myMemory->boss->GetEyeBeamMesh()->SetRelativeScale3D(initScale);
		myMemory->boss->SetEyeBeamActivated(true);
		myMemory->boss->GetEyeBeamMaterial()->SetVectorParameterValue("Color", FColor::White);
		myMemory->boss->GetEyeBeamMaterial()->SetScalarParameterValue("Opacity", 1.f);

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

uint16 UBTT_EyeBeamAttack::GetInstanceMemorySize() const
{
	return sizeof(FBTEyeBeamAttack);
}

void UBTT_EyeBeamAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	if (!OwnerComp.GetAIOwner())
	{
		return;
	}


	FBTEyeBeamAttack* myMemory = reinterpret_cast<FBTEyeBeamAttack*>(NodeMemory);
	
	if (myMemory->boss->GetIsDead())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);
	}

	myMemory->timerToAttack -= DeltaSeconds;


	if (myMemory->timerToAttack > timerToAttackValue / 2)
	{
		FVector growScale = FVector(myMemory->boss->GetEyeBeamMesh()->GetRelativeScale3D().X + (myMemory->deltaProgress * DeltaSeconds), myMemory->boss->GetEyeBeamMesh()->GetRelativeScale3D().Y, myMemory->boss->GetEyeBeamMesh()->GetRelativeScale3D().Z);
		myMemory->boss->GetEyeBeamMesh()->SetRelativeScale3D(growScale);
	}
	else
	{
		FVector growScale = FVector(myMemory->boss->GetEyeBeamMesh()->GetRelativeScale3D().X - (myMemory->deltaProgress * DeltaSeconds), myMemory->boss->GetEyeBeamMesh()->GetRelativeScale3D().Y, myMemory->boss->GetEyeBeamMesh()->GetRelativeScale3D().Z);
		myMemory->boss->GetEyeBeamMesh()->SetRelativeScale3D(growScale);
	}


	if (myMemory->timerToAttack <= 0)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Timer %f"), myMemory->timerToAttack));
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("grow Scale %s"), *myMemory->boss->GetEyeBeamMesh()->GetRelativeScale3D().ToString()));

}
