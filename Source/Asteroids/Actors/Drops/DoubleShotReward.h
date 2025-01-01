// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Drops/RewardItem.h"
#include "DoubleShotReward.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API ADoubleShotReward : public ARewardItem
{
	GENERATED_BODY()
	protected:
	virtual void Effect(class ASpaceship* player) override;
};
