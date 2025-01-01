// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AsteroidGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API AAsteroidGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	int GetCurrentRound() {return currentRound;};
	UFUNCTION(BlueprintCallable,BlueprintPure)
	int GetMaxRound() {return maxRound;};

	void GoToNextRound();

	bool GetGamePlaying() {return b_gamePlaying;};

	void SetGamePlaying(bool _b);

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool  GetBossFight() {return b_bossFight;};

	void ResetGame();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetGameWin() {return b_win; };
	void SetGameWin(bool _b) {b_win = _b; };
protected:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ARewardItem>> rewardArray;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABoss> bossReference;

	int currentRewardIndex = 0;
	UPROPERTY(EditAnywhere)
	int currentRound = 1;
	UPROPERTY(EditAnywhere)
	int maxRound = 6;

	UPROPERTY(EditAnywhere)
	float roundTimerValue = 30;
	float roundTimer;

	void SpawnRewardItem();

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;
	

	bool b_gamePlaying = true;
	bool b_bossFight = false;
	bool b_win =false;

};
