// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Entities/Boss.h"
#include "Actors/Arena.h"
#include "Actors/Drops/RewardItem.h"

void AAsteroidGameMode::GoToNextRound()
{
	currentRound++;
	roundTimer = roundTimerValue;

	if (currentRound % 3 == 0)
	{
		b_gamePlaying = false;
		SpawnRewardItem();
	}
}




void AAsteroidGameMode::SetGamePlaying(bool _b)
{
	if (currentRound < maxRound)
	{
		b_gamePlaying = _b;
	}
	else
	{
		b_bossFight = _b;
		if (bossReference &&  UGameplayStatics::GetActorOfClass(GetWorld(), AArena::StaticClass()))
		{
			AArena* arena = Cast<AArena>(UGameplayStatics::GetActorOfClass(GetWorld(), AArena::StaticClass()));
			if (arena)
			{
				arena->SpawnBoss(bossReference);
			}
		}
	}
}

void AAsteroidGameMode::ResetGame()
{
	currentRound = 1;
	currentRewardIndex = 0;
	b_bossFight =false;
	b_win = false;
	b_gamePlaying = true;

	if (UGameplayStatics::GetActorOfClass(GetWorld(), ABoss::StaticClass()))
	{
		Cast<ABoss>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoss::StaticClass()))->RemoveFromArena();
	}
}

void AAsteroidGameMode::SpawnRewardItem()
{
	if (rewardArray.Num() > 0 && currentRewardIndex < rewardArray.Num() && UGameplayStatics::GetActorOfClass(GetWorld(), AArena::StaticClass()))
	{
		AArena* arena = Cast<AArena>(UGameplayStatics::GetActorOfClass(GetWorld(), AArena::StaticClass()));
		if (arena && rewardArray[currentRewardIndex])
		{
			if (Cast<ARewardItem>(rewardArray[currentRewardIndex]->GetDefaultObject()))
			{
				arena->SpawnReward(rewardArray[currentRewardIndex]);
			}
		}
	}
	currentRewardIndex++;
}

void AAsteroidGameMode::BeginPlay()
{
	Super::BeginPlay();

	roundTimer = roundTimerValue;
}

void AAsteroidGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (b_gamePlaying)
	{
		roundTimer -= DeltaSeconds;
		if (roundTimer <= 0)
		{
			GoToNextRound();
		}
	}

}
