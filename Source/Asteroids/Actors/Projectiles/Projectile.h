// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


class UBoxComponent;
class UProjectileMovementComponent;

UCLASS()
class ASTEROIDS_API AProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UBoxComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UBoxComponent* boxCollider;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AProjectile();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* mesh;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UBoxComponent* GetCollisionComp() const { return CollisionComp; }
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	void SetOwner(class AActor* _nw) { owner = _nw; };

	int GetDamage() {return damage;};

protected:
	virtual void BeginPlay() override;

	class AActor* owner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int damage = 1;

public:
	virtual void Tick(float DeltaTime) override;
};
