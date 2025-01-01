// Fill out your copyright notice in the Description page of Project Settings.


#include "../Drops/ShieldReward.h"
#include "../Entities/Spaceship.h"
#include "../../CustomComponents/ShieldComponent.h"
#include "Components/BoxComponent.h"
#include "../../AsteroidGameMode.h"


void AShieldReward::Effect(ASpaceship* player)
{
	if (player)
	{
		player->GetShieldComponent()->SetIsAvailable(true);
	}
	Destroy();
}

