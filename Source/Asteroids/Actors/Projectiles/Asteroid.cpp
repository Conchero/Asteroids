// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectiles/Asteroid.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Entities/Spaceship.h"
#include "PlayerProjectile.h"

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();


	GetProjectileMovement()->InitialSpeed = FMath::RandRange(minSpeed, maxSpeed);
	GetProjectileMovement()->MaxSpeed = GetProjectileMovement()->InitialSpeed;
	GetProjectileMovement()->ProjectileGravityScale = 0.f;

	//If asteroids supposed to split can have more than the base split
	if (nbSplit > 0)
	{
		nbSplit = FMath::RandRange(nbSplit, nbSplit+3);
	}
}

void AAsteroid::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnHit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (Cast<APlayerProjectile>(OtherActor))
	{
		OtherActor->Destroy();
		Death();
	}
}

void AAsteroid::Death()
{

	if (nbSplit > 0)
	{
		for (int i = 0; i < nbSplit; i++)
		{
			AAsteroid* spawnedSplit = GetWorld()->SpawnActorDeferred<AAsteroid>(asteroidSplit, GetTransform());
			spawnedSplit->SetActorLocation(GetActorLocation());

			spawnedSplit->minSpeed = minSpeed / (FMath::RandRange(1, 2));
			spawnedSplit->maxSpeed = maxSpeed / (FMath::RandRange(1, 2));

			AActor* player = UGameplayStatics::GetActorOfClass(GetWorld(), ASpaceship::StaticClass());
			FRotator direction = UKismetMathLibrary::FindLookAtRotation(spawnedSplit->GetActorLocation(), player->GetActorLocation());
			float yawDirection = direction.Yaw + FMath::RandRange(-90.f, 90.f);

			spawnedSplit->SetActorRotation(FRotator(0, yawDirection, 0));
			spawnedSplit->FinishSpawning(GetTransform());
		}
	}


	Destroy();

}
