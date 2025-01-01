// Fill out your copyright notice in the Description page of Project Settings.


#include "../CustomComponents/ShieldComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HealthComponent.h"

// Sets default values for this component's properties
UShieldComponent::UShieldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UShieldComponent::ResetShield()
{
	DesactivateShield();
	SetIsAvailable(false);
}

void UShieldComponent::ActivateShield(UStaticMeshComponent* _sts)
{
	if (healthComponent)
	{
		if (_sts)
		{
			shieldMeshToShow = _sts;
			shieldMeshToShow->SetVisibility(true);
		}
		healthComponent->SetInvunerability(true);
		b_shieldActivated = true;
	}
}

void UShieldComponent::DesactivateShield()
{
	b_shieldActivated = false;
	if (shieldMeshToShow)
	{
		shieldMeshToShow->SetVisibility(false);
		shieldMeshToShow = nullptr;
	}
	if (healthComponent)
	{
		healthComponent->SetInvunerability(false);
	}
}

// Called when the game starts
void UShieldComponent::BeginPlay()
{
	Super::BeginPlay();
	shieldTimer= timerMaxValue;
	// ...
	
}


// Called every frame
void UShieldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (b_shieldActivated)
	{
		shieldTimer -= DeltaTime;
		if (shieldTimer<=0)
		{
			b_shieldActivated = false;
			DesactivateShield();
		}
	}

	if (!b_shieldActivated)
	{
		if (shieldTimer < timerMaxValue)
		{
			shieldTimer += DeltaTime/2;		
		}
		else
		{
			DesactivateShield();
		}
	}


	// ...
}

