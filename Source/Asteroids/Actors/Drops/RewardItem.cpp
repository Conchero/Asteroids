// Fill out your copyright notice in the Description page of Project Settings.


#include "../Drops/RewardItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "../Entities/Spaceship.h"
#include "../../AsteroidGameMode.h"

// Sets default values
ARewardItem::ARewardItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	mesh->SetupAttachment(RootComponent);

	collider = CreateDefaultSubobject<UBoxComponent>("collider");
	collider->SetupAttachment(mesh);
}

// Called when the game starts or when spawned
void ARewardItem::BeginPlay()
{
	Super::BeginPlay();
	collider->OnComponentBeginOverlap.AddDynamic(this, &ARewardItem::OnBeginOverlap);

}

void ARewardItem::Effect(class ASpaceship* player)
{

}

void ARewardItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ASpaceship>(OtherActor))
	{
		Effect(Cast<ASpaceship>(OtherActor));

		if (GetWorld()->GetAuthGameMode<AAsteroidGameMode>())
		{
			AAsteroidGameMode* gameMode = GetWorld()->GetAuthGameMode<AAsteroidGameMode>();
			gameMode->SetGamePlaying(true);
		}
	}
}

// Called every frame
void ARewardItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

