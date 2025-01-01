// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectiles/PlayerProjectile.h"

APlayerProjectile::APlayerProjectile()
{
	InitialLifeSpan = 3.f;
}

void APlayerProjectile::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnHit(OverlappedComponent,OtherActor,OtherComp,OtherBodyIndex,bFromSweep,SweepResult);

}
