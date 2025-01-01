// Fill out your copyright notice in the Description page of Project Settings.


#include "../Drops/DoubleShotReward.h"
#include "../Entities/Spaceship.h"
#include "../../CustomComponents/ShootComponent.h"

void ADoubleShotReward::Effect( ASpaceship* player)
{
	if (player)
	{
		player->GetShootComponent()->SetNbShot(2);
	}

	Destroy();
}
