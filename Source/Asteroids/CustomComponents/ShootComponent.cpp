// Fill out your copyright notice in the Description page of Project Settings.


#include "../CustomComponents/ShootComponent.h"
#include "../Actors/Projectiles/Projectile.h"

// Sets default values for this component's properties
UShootComponent::UShootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UShootComponent::OnFire(bool _b, int _direction)
{
	b_firing = _b;

	//Shoot direction and spaceship rotation aren't related so i had to do this
	//To upgrade
	switch (_direction)
	{
	case 0:
		shootDirection = 90;
		break;
	case 180:
		shootDirection = -90;
		break;
	case -90:
		shootDirection = 0;
		break;
	case 90:
		shootDirection = 180;
		break;
	}

	if (!b_firing)
	{
		fireRate = fireRateValue;
	}
}

// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


void UShootComponent::FireManagement(float _dt)
{
	if (b_firing)
	{
		fireRate -= _dt;
		if (fireRate <= 0)
		{
			Fire();
			fireRate = fireRateValue;
		}
	}
}

void UShootComponent::Fire(float speed)
{

	if (projectile)
	{
		for (int i = 0; i < nbShot; i++)
		{
			FRotator spawnRotation = FRotator(0, shootDirection, 90);
			FActorSpawnParameters spawnParams = FActorSpawnParameters();
			AProjectile* shotProjectile = GetWorld()->SpawnActorDeferred<AProjectile>(projectile, GetOwner()->GetTransform());
			shotProjectile->SetActorHiddenInGame(true);
			FVector shotLocation = FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, GetOwner()->GetActorLocation().Z);

			if (nbShot > 1)
			{
				if (FMath::Abs(shootDirection) == 90)
				{
					shotLocation.X += i == 0 ? -10 : 10;
				}
				else
				{
					shotLocation.Y += i == 0 ? -10 : 10;
				}
			}

			shotProjectile->SetActorLocation(shotLocation);
			shotProjectile->SetActorRotation(spawnRotation);
			shotProjectile->SetOwner(GetOwner());
			shotProjectile->FinishSpawning(GetOwner()->GetTransform());
			shotProjectile->SetActorHiddenInGame(false);
		}
	}
}

// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FireManagement(DeltaTime);
	// ...
}

void UShootComponent::SetFireRate(float _v)
{
	fireRateValue = _v;
	fireRateValue = FMath::Clamp(fireRateValue, maxFireRate, baseFireRate);
}

