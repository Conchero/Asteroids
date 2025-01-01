// Fill out your copyright notice in the Description page of Project Settings.


#include "../Entities/EnemyEntity.h"
#include "../Entities/Spaceship.h"
#include "Kismet/GameplayStatics.h"
#include "../../CustomComponents/HealthComponent.h"
#include "Components/BoxComponent.h"
void AEnemyEntity::Death()
{
	if (UGameplayStatics::GetActorOfClass(GetWorld(), ASpaceship::StaticClass()))
	{
		ASpaceship* spaceShip = Cast<ASpaceship>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpaceship::StaticClass()));
		spaceShip->SetScore(spaceShip->GetScore() + scoreValue);
	}
}

void AEnemyEntity::OnTouchBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ASpaceship>(OtherActor))
	{
		Cast<ASpaceship>(OtherActor)->GetHealthComponent()->RemoveLife(damage);
	}
}

void AEnemyEntity::BeginPlay()
{
Super::BeginPlay();

	boxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this,&AEnemyEntity::OnTouchBeginOverlap);
}
