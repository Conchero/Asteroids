// Fill out your copyright notice in the Description page of Project Settings.


#include "../Entities/Entity.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "../../CustomComponents/HealthComponent.h"

// Sets default values
AEntity::AEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");
	
	//root component was not accesible in blueprint so i had to do this
	container = CreateDefaultSubobject<USceneComponent>("root_component");

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	mesh->SetupAttachment(container);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComponent");

	boxCollider = CreateDefaultSubobject<UBoxComponent>("boxCollider");
	boxCollider->SetupAttachment(container);

	healthComponent = CreateDefaultSubobject<UHealthComponent>("healthComponent");

}

void AEntity::Death()
{

}

void AEntity::OnHealthChange()
{

}

void AEntity::OnCanTakeDamageRestored()
{

}

// Called when the game starts or when spawned
void AEntity::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

