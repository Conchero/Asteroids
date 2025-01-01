// Fill out your copyright notice in the Description page of Project Settings.


#include "../CustomComponents/BossShootComponent.h"
#include "../Actors/Projectiles/Projectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UBossShootComponent::OnFire(bool _b, int _direction /*= 0*/)
{

	b_firing = _b;

}

void UBossShootComponent::SingleShoot()
{
	Fire();	
}

UBossShootComponent::UBossShootComponent()
{
	nbShot = 3;

}

void UBossShootComponent::Fire(float speed)
{
	if (projectile)
	{

		int trueNbShot = nbShot + 1;
		for (int i = 1; i < trueNbShot; i++)
		{
			FRotator shootRotator = FRotator(0, (180 / trueNbShot) * i, 0);
			FVector pointsAroundCircle = UKismetMathLibrary::GetForwardVector(shootRotator);

			FVector dotPosition = (pointsAroundCircle * 50) + GetOwner()->GetActorLocation();
			dotPosition = FVector(dotPosition.X,dotPosition.Y + shotFromCannonDistance , dotPosition.Z);

			DrawDebugPoint(GetWorld(), dotPosition, 4, FColor::Red, false, 2.f);

			AProjectile* spawnedProjectile = GetWorld()->SpawnActor<AProjectile>(projectile, dotPosition,shootRotator);
			if (speed > 0)
			{
				spawnedProjectile->GetProjectileMovement()->InitialSpeed = speed;
				spawnedProjectile->GetProjectileMovement()->MaxSpeed =speed;
			}
		}
	}
}
