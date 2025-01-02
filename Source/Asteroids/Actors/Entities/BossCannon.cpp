// Fill out your copyright notice in the Description page of Project Settings.


#include "../Entities/BossCannon.h"
#include "../Entities/Boss.h"
#include "../../CustomComponents/BossShootComponent.h"
#include "Spaceship.h"
#include "../../CustomComponents/HealthComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

ABossCannon::ABossCannon()
{
	shootComponent = CreateDefaultSubobject<UBossShootComponent>("shootComponent");
}

void ABossCannon::Death()
{
	cannonDynMaterial->SetVectorParameterValue("Color", FColor(155, 155, 155));
	cannonDynMaterial->SetScalarParameterValue("Opacity", 0.2f);
	b_dead = true;
	SetMovement(false);


	if (bossParent->GetPartsAlive().Num() == 0)
	{
		bossParent->BossKilled();
	}
}

void ABossCannon::SingleShoot()
{
	//used for random attack to bypass firerate
	if (!b_dead && shootComponent)
	{
		shootComponent->SingleShoot();
	}
}

bool ABossCannon::CheckPlayerCannonRaycast()
{
	//raycast from each limits
	if (!b_dead && translationLimits.Num() > 0)
	{
		FHitResult hitResult;

		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(this);
		if (bossParent)
		{
			queryParams.AddIgnoredActor(bossParent);
		}

		int rayCastZone = FMath::Abs(translationLimits[1] - translationLimits[0]);

		for (int i = 0; i < rayCastZone / 10; i++)
		{
			FVector lineStart = FVector(translationLimits[0] + (i * 10), GetActorLocation().Y, GetActorLocation().Z);
			FVector lineEnd = FVector(translationLimits[0] + (i * 10), GetActorLocation().Y + 1080, GetActorLocation().Z);

			GetWorld()->LineTraceSingleByChannel(hitResult, lineStart, lineEnd, ECollisionChannel::ECC_Pawn, queryParams);
			if (hitResult.bBlockingHit && Cast<ASpaceship>(hitResult.GetActor()))
			{
				return true;
			}
		}

	}
	return false;
}

void ABossCannon::OnHealthChange()
{
	if (!b_dead)
	{
		cannonDynMaterial->SetVectorParameterValue("Color", FColor::Red);
	}
}

void ABossCannon::OnCanTakeDamageRestored()
{
	if (!b_dead)
	{
		cannonDynMaterial->SetVectorParameterValue("Color", FColor::White);
	}
}

void ABossCannon::Move(float _dt)
{
	if (!b_dead &&  translationLimits.Num() >= 2 && isMoving)
	{
		FVector2D newPosition = FVector2D(GetActorLocation().X + ((translationSpeed * _dt) * translationDirection), GetActorLocation().Y);
		SetActorLocation(FVector(newPosition.X, newPosition.Y, GetActorLocation().Z));

		if (GetActorLocation().X < translationLimits[0] || GetActorLocation().X > translationLimits[1])
		{
			translationDirection *= -1;
		}
	}
}

void ABossCannon::BeginPlay()
{
	Super::BeginPlay();

	cannonDynMaterial = UMaterialInstanceDynamic::Create(mesh->GetMaterial(0), this);
	mesh->SetMaterial(0, cannonDynMaterial);
}

void ABossCannon::Tick(float DeltaTime)
{
	Move(DeltaTime);
}
