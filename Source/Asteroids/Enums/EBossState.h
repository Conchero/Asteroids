// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//used in behavior tree
UENUM(BlueprintType)
enum class EBossState : uint8
{
	LOADING_ATTACK  = 0,
	LEFT_CANNON_ATTACK = 1,
	EYE_CANNON_ATTACK = 2,
	RIGHT_CANNON_ATTACK = 3,
};