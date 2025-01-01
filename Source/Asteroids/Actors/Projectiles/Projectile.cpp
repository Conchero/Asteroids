// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectiles/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("boxCollider"));
	boxCollider->BodyInstance.SetCollisionProfileName("Projectile");
	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something blocking
	
	// Players can't walk on it
	boxCollider->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	boxCollider->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = boxCollider;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = 10.f;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}