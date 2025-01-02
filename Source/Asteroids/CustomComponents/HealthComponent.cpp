// Fill out your copyright notice in the Description page of Project Settings.


#include "../CustomComponents/HealthComponent.h"
#include "../Actors/Entities/Spaceship.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
}


void UHealthComponent::RemoveLife(int _nb)
{
	if (b_canTakeDamage && !b_haveInvunerability)
	{
		currentHealth -= _nb;
		b_canTakeDamage = false;

		if (currentHealth <= 0)
		{
			Death();
		}

		if (GetParentEntity())
			GetParentEntity()->OnHealthChange();
	}
}

void UHealthComponent::AddLife(int _nb)
{
	currentHealth += _nb;
	currentHealth = FMath::Clamp(currentHealth, 0, maxHealth);

	if (GetParentEntity())
		GetParentEntity()->OnHealthChange();
}

void UHealthComponent::Death()
{
	if (GetParentEntity())
		GetParentEntity()->Death();
}



class AEntity* UHealthComponent::GetParentEntity()
{
	if (parentEntity)
	{
		return parentEntity;

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ParentEntity was null in Health component"));
	}

	return nullptr;

}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	currentHealth = maxHealth;
	noDamageCooldown = noDamageCooldownValue;
	if (Cast<AEntity>(GetOwner()))
	{
		parentEntity = Cast<AEntity>(GetOwner());
	}

}

//Can't take damage after taking a hit for a certain period of time
void UHealthComponent::NoDamageCooldownManagement(float _dt)
{
	if (!b_canTakeDamage)
	{
		noDamageCooldown -= _dt;
		if (noDamageCooldown <= 0)
		{
			noDamageCooldown = noDamageCooldownValue;
			b_canTakeDamage = true;
			if (GetParentEntity())
			{
				GetParentEntity()->OnCanTakeDamageRestored();
			}
		}
	}

}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	NoDamageCooldownManagement(DeltaTime);
}

