// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actors/Arena.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
#include "../Actors/Entities/Entity.h"
#include "../Actors/Entities/Boss.h"
#include "../Actors/Projectiles/Asteroid.h"
#include "Kismet/GameplayStatics.h"
#include "Entities/Spaceship.h"
#include "Kismet/KismetMathLibrary.h"
#include "../AsteroidGameMode.h"
#include "Drops/RewardItem.h"

// Sets default values
AArena::AArena()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AArena::BeginPlay()
{
	Super::BeginPlay();
	//Ue scale in cm so x100
	width = GetActorScale3D().X * 100;
	height = GetActorScale3D().Y * 100;
}

void AArena::SpawnEnemyManagement(float _dt)
{
	timerBeforeSpawnEnemy -= _dt;

	if (timerBeforeSpawnEnemy <= 0)
	{
		if (typeOfAsteroidArray.Num() > 0)
		{
			int asteroidIndex = FMath::RandRange(0, typeOfAsteroidArray.Num() - 1);
			if (asteroidIndex < typeOfAsteroidArray.Num() && typeOfAsteroidArray[asteroidIndex])
			{

				AActor* player = UGameplayStatics::GetActorOfClass(GetWorld(), ASpaceship::StaticClass());
				if (player && !Cast<ASpaceship>(player)->GetIsDead())
				{
					AEntity* spawnedEntity = GetWorld()->SpawnActorDeferred<AEntity>(typeOfAsteroidArray[asteroidIndex], GetTransform());
					float spawnX = FMath::RandRange(-width / 2, width / 2);
					float spawnY = FMath::RandRange(-height / 2, height / 2);
					//Avoid Spawn on player
					spawnedEntity->SetActorLocation(FVector(player->GetActorLocation().X + spawnX, player->GetActorLocation().Y + spawnY, player->GetActorLocation().Z));
					FRotator lookAtPlayer = UKismetMathLibrary::FindLookAtRotation(spawnedEntity->GetActorLocation(), player->GetActorLocation());
					spawnedEntity->SetActorRotation(FRotator(0, lookAtPlayer.Yaw, 0));
					spawnedEntity->FinishSpawning(GetTransform());
				}

			}
		}
		if (GetWorld()->GetAuthGameMode<AAsteroidGameMode>())
		{
			AAsteroidGameMode* gameMode = GetWorld()->GetAuthGameMode<AAsteroidGameMode>();
			float timerReducer = (gameMode->GetCurrentRound() / 10);

			timerBeforeSpawnEnemy = FMath::RandRange(1.f - timerReducer, timerBeforeSpawnEnemyValue - timerReducer);
		}
	}
}


void AArena::SpawnReward(TSubclassOf<ARewardItem> _ri)
{
	if (_ri)
	{
		AActor* player = UGameplayStatics::GetActorOfClass(GetWorld(), ASpaceship::StaticClass());
		if (player && !Cast<ASpaceship>(player)->GetIsDead())
		{
			FVector spawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, player->GetActorLocation().Z);
			FActorSpawnParameters spawnParams = FActorSpawnParameters();
			GetWorld()->SpawnActor<AActor>(_ri, spawnLocation, FRotator::ZeroRotator, spawnParams);
		}
	}
}

void AArena::SpawnBoss(TSubclassOf<class ABoss> _b)
{
	if (_b)
	{
		AActor* player = UGameplayStatics::GetActorOfClass(GetWorld(), ASpaceship::StaticClass());
		if (player && !Cast<ASpaceship>(player)->GetIsDead())
		{
			FVector spawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y - (GetArenaHeight()/2) + heightBossSpawn, player->GetActorLocation().Z);
			GetWorld()->SpawnActor<ABoss>(_b,spawnLocation, FRotator::ZeroRotator);
		}
	}
}

// Called every frame
void AArena::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->GetAuthGameMode<AAsteroidGameMode>())
	{
		AAsteroidGameMode* gameMode = GetWorld()->GetAuthGameMode<AAsteroidGameMode>();
		if (gameMode->GetGamePlaying())
		{
			SpawnEnemyManagement(DeltaTime);
		}
	}
}

