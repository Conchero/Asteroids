// Fill out your copyright notice in the Description page of Project Settings.


#include "../Entities/AsteroidEnemy.h"
#include "../Drops/Drop.h"
#include "../Entities/AsteroidSplit.h"
#include "../Entities/SpaceShip.h"
#include "../Projectiles/PlayerProjectile.h"
#include "../../CustomComponents/HealthComponent.h"
#include "../../CustomComponents/DestroyWhenOutOfBounds.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Arena.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../AsteroidGameMode.h"

AAsteroidEnemy::AAsteroidEnemy()
{
	distanceComponent = CreateDefaultSubobject<UDestroyWhenOutOfBounds>("Distance component");
}


void AAsteroidEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (UGameplayStatics::GetActorOfClass(GetWorld(), AArena::StaticClass()))
	{
		distanceComponent->SetTrackedActor(UGameplayStatics::GetActorOfClass(GetWorld(), AArena::StaticClass()));
	}

	SetSpeedAndDirection();
}

void AAsteroidEnemy::Death()
{

	Super::Death();

	if (Cast<AAsteroidGameMode>(GetWorld()->GetAuthGameMode()))
	{
		AAsteroidGameMode* asteroidGameMode = Cast<AAsteroidGameMode>(GetWorld()->GetAuthGameMode());
		if (FMath::RandRange(0, 100) > (dropChance + (asteroidGameMode->GetCurrentRound() * 10)))
		{
			SortDropObject();
		}
		AsteroidSplit(asteroidGameMode);

	}



	Destroy();
}

void AAsteroidEnemy::AsteroidSplit(AAsteroidGameMode* _gm)
{
	int trueNbSplit =  FMath::RandRange(nbSplit, nbSplit+ _gm->GetCurrentRound());
	for (int i = 1; i < trueNbSplit; i++)
	{
		FRotator randomRotator = FRotator(0, (int)(FMath::RandRange(0, 360)), 0);
		if (UGameplayStatics::GetActorOfClass(GetWorld(), ASpaceship::StaticClass()))
		{
			AActor* spaceShip = UGameplayStatics::GetActorOfClass(GetWorld(), ASpaceship::StaticClass());
			FRotator lookAtPlayer = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), spaceShip->GetActorLocation());
			randomRotator += lookAtPlayer;
		}
		FVector pointsAroundCircle = UKismetMathLibrary::GetForwardVector(FRotator(0, (360 / trueNbSplit) * i, 0) + randomRotator);

		FVector dotPosition = (pointsAroundCircle * 50) + GetActorLocation();

		if (asteroidSplit)
		{
			AAsteroidSplit* spawnedSplit = GetWorld()->SpawnActorDeferred<AAsteroidSplit>(asteroidSplit, GetTransform());
			spawnedSplit->SetActorLocation(dotPosition);
			spawnedSplit->SetActorRotation(randomRotator);
			spawnedSplit->SetParentActor(this);
			spawnedSplit->FinishSpawning(GetTransform());
			spawnedSplit->SetSpeedAndDirection();
		}
	}
}

void AAsteroidEnemy::SortDropObject()
{
	if (dropObjectArray.Num() > 0)
	{

		TSubclassOf<ADrop> dropToSpawn = nullptr;
		TMap<TSubclassOf<ADrop>, TArray<int>> dropPull;
		int maximumValue = 0;

		for (TSubclassOf<ADrop> subClassDrop : dropObjectArray)
		{
			if (Cast<ADrop>(subClassDrop->GetDefaultObject()))
			{
				ADrop* dropObject = Cast<ADrop>(subClassDrop->GetDefaultObject());
				TArray<int> dropChanceScale = { maximumValue,maximumValue + dropObject->GetDropChance() };
				maximumValue += dropObject->GetDropChance();

				dropPull.Emplace(subClassDrop, dropChanceScale);
			}
		}

		int randomNumber = FMath::RandRange(0, maximumValue);

		if (dropPull.Num() > 0)
		{
			for (auto& dropMap : dropPull)
			{
				if (randomNumber > dropMap.Value[0] && randomNumber < dropMap.Value[1])
				{
					dropToSpawn = dropMap.Key;
				}
			}
		}

		if (dropToSpawn)
		{
			FActorSpawnParameters spawnParameters = FActorSpawnParameters();
			GetWorld()->SpawnActor<ADrop>(dropToSpawn, GetActorLocation(), FRotator::ZeroRotator, spawnParameters);
		}

	}

}

void AAsteroidEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PositionOverTime(DeltaTime);
}

void AAsteroidEnemy::SetSpeedAndDirection()
{

	if (distanceComponent->GetActorToTrack())
	{
		if (distanceComponent->CalculateDistanceFromActor().X * -1 > 0)
		{
			velocity.X = 1;
		}
		else
		{
			velocity.X = -1;
		}
		if (distanceComponent->CalculateDistanceFromActor().Y * -1 > 0)
		{
			velocity.Y = 1;
		}
		else
		{
			velocity.Y = -1;
		}
	}

	speed = FMath::RandRange(minSpeed, maxSpeed);
}

void AAsteroidEnemy::PositionOverTime(float deltaTime)
{
	FVector2D position;
	position.X = GetActorLocation().X + ((speed * velocity.X) * deltaTime);
	position.Y = GetActorLocation().Y + ((speed * velocity.Y) * deltaTime);
	SetActorLocation(FVector(position.X, position.Y, GetActorLocation().Z));
}


