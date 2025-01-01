// Fill out your copyright notice in the Description page of Project Settings.


#include "../Entities/Boss.h"
#include "../Entities/BossCannon.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "../Arena.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Spaceship.h"
#include "Components/BoxComponent.h"
#include "../../CustomComponents/HealthComponent.h"
#include "../../AsteroidGameMode.h"

ABoss::ABoss()
{
	behaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>("behaviorTree");

	eyeBeamMesh = CreateDefaultSubobject<UStaticMeshComponent>("Eye Beam");
	eyeBeamMesh->SetupAttachment(container);
	eyeBeamCollider = CreateDefaultSubobject<UBoxComponent>("eye beam collider");
	eyeBeamCollider->SetupAttachment(container);


}


void ABoss::SetMoveCannon(bool _b)
{
	if (bossRightCannon)
		bossRightCannon->SetMovement(_b);

	if (bossLeftCannon)
		bossLeftCannon->SetMovement(_b);
}

void ABoss::Death()
{
	b_dead = true;
	eyeDynMaterial->SetVectorParameterValue("Color", FColor(155, 155, 155));
	eyeDynMaterial->SetScalarParameterValue("Opacity", 0.2f);
	ResetEyeBeamMeshAndMaterial();

	if (GetPartsAlive().Num() == 0)
	{
		BossKilled();
	}
}

void ABoss::OnHealthChange()
{
	if (!b_dead)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Eye health %d"), GetHealthComponent()->GetHealth()));
		eyeDynMaterial->SetVectorParameterValue("Color", FColor::Red);
	}
	
}


void ABoss::OnCanTakeDamageRestored()
{
	if (!b_dead)
	{
	eyeDynMaterial->SetVectorParameterValue("Color", FColor::White);
	}

}

void ABoss::BossKilled()
{
	GetWorld()->GetAuthGameMode<AAsteroidGameMode>()->SetGameWin(true);
	RemoveFromArena();
}

void ABoss::RemoveFromArena()
{
	if (bossLeftCannon)
	bossLeftCannon->Destroy();

	if (bossRightCannon)
	bossRightCannon->Destroy();

	Destroy();
}

TArray<int> ABoss::GetPartsAlive()
{
	TArray<int> partsAlive;

	if (!b_dead)
	{
		partsAlive.Add(1);
	}

	if (!bossRightCannon->GetIsDead())
	{
		partsAlive.Add(2);
	}

	if (!bossLeftCannon->GetIsDead())
	{
		partsAlive.Add(0);
	}
	return partsAlive;
}


void ABoss::ResetEyeBeamMeshAndMaterial()
{
	GetEyeBeamMesh()->SetRelativeScale3D(baseEyeBeamScale);
	GetEyeBeamMaterial()->SetScalarParameterValue("Opacity", baseEyeBeamOpacity);
	GetEyeBeamMaterial()->SetVectorParameterValue("Color", baseEyeBeamColor);
	GetEyeBeamMesh()->SetHiddenInGame(true);
	SetEyeBeamActivated(false);
}

void ABoss::SetEyeBeamActivated(bool _b)
{
	if (!b_dead)
		eyeBeamActivated = _b;
}

int ABoss::CheckPlayerPresence()
{
	//0 boss left cannon,  1 boss eye, 2 boss right cannon 
	//used to check where the player is most likely to be to choose an attack
	if ( !b_dead && CheckPlayerBossEyeRaycast())
	{
		return 1;
	}


	if (bossRightCannon && !bossRightCannon->GetIsDead())
	{
		if (bossRightCannon->CheckPlayerCannonRaycast())
			return 2;
	}

	if (bossLeftCannon && !bossLeftCannon->GetIsDead())
	{
		if (bossLeftCannon->CheckPlayerCannonRaycast())
			return 0;
	}

	return -1;
}



bool ABoss::CheckPlayerBossEyeRaycast()
{
	if (bossLeftCannon && bossRightCannon)
	{
		FHitResult hitResult;
		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(this);
		queryParams.AddIgnoredActor(bossLeftCannon);
		queryParams.AddIgnoredActor(bossRightCannon);

		int rayCastZone = FMath::Abs(bossLeftCannon->GetTranslationLimits()[1] - bossRightCannon->GetTranslationLimits()[0]);

		for (int i = 0; i < rayCastZone / 10; i++)
		{
			FVector lineStart = FVector(bossLeftCannon->GetTranslationLimits()[1] + (i * 10), GetActorLocation().Y, GetActorLocation().Z);
			FVector lineEnd = FVector(bossLeftCannon->GetTranslationLimits()[1] + (i * 10), GetActorLocation().Y + 1080, GetActorLocation().Z);

			GetWorld()->LineTraceSingleByChannel(hitResult, lineStart, lineEnd, ECollisionChannel::ECC_Pawn, queryParams);
			if (hitResult.bBlockingHit && Cast<ASpaceship>(hitResult.GetActor()))
			{
				return true;
			}
			DrawDebugLine(GetWorld(), lineStart, lineEnd, hitResult.bBlockingHit ? FColor::Red : FColor::Magenta, false, 1.0f);
		}
	}
	return false;
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();


	if (UGameplayStatics::GetActorOfClass(GetWorld(), AArena::StaticClass()))
	{
		AArena* arena = Cast<AArena>(UGameplayStatics::GetActorOfClass(GetWorld(), AArena::StaticClass()));

		FVector rightCannonLocation = FVector(GetActorLocation().X + cannonDistanceFromEye, GetActorLocation().Y, GetActorLocation().Z);
		bossRightCannon = GetWorld()->SpawnActor<ABossCannon>(bossRightCannonRef, rightCannonLocation, FRotator::ZeroRotator);
		TArray<int> rightCannonLimits = { (int)(GetActorLocation().X + eyeWidth) , arena->GetArenaWidth() / 2 - bossRightCannon->GetCannonWidth() };
		bossRightCannon->SetLimits(rightCannonLimits);
		bossRightCannon->SetBossParent(this);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("limit %d limit %d"), rightCannonLimits[0], rightCannonLimits[1]));

		FVector leftCannonLocation = FVector(GetActorLocation().X - cannonDistanceFromEye, GetActorLocation().Y, GetActorLocation().Z);
		bossLeftCannon = GetWorld()->SpawnActor<ABossCannon>(bossLeftCannonRef, leftCannonLocation, FRotator::ZeroRotator);
		TArray<int> leftCannonLimits = { -(arena->GetArenaWidth() / 2) + bossLeftCannon->GetCannonWidth(), (int)(GetActorLocation().X - eyeWidth) };
		bossLeftCannon->SetLimits(leftCannonLimits);
		bossLeftCannon->SetBossParent(this);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("limit %d limit %d"), leftCannonLimits[0], leftCannonLimits[1]));

	}

	eyeDynMaterial = UMaterialInstanceDynamic::Create(mesh->GetMaterial(0), this);
	mesh->SetMaterial(0, eyeDynMaterial);

	baseEyeBeamScale = GetEyeBeamMesh()->GetRelativeScale3D();
	eyeBeamDynMaterial = UMaterialInstanceDynamic::Create(eyeBeamMesh->GetMaterial(0), this);
	baseEyeBeamColor = eyeBeamDynMaterial->K2_GetVectorParameterValue("Color");
	baseEyeBeamOpacity = eyeBeamDynMaterial->K2_GetScalarParameterValue("Opacity");
	eyeBeamMesh->SetMaterial(0, eyeBeamDynMaterial);


}

void ABoss::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (eyeBeamActivated)
	{
		TArray<AActor*> overlappingActor;
		eyeBeamCollider->GetOverlappingActors(overlappingActor, ASpaceship::StaticClass());
		if (overlappingActor.Num() > 0)
		{
			for (auto actor : overlappingActor)
			{
				if (Cast<ASpaceship>(actor))
				{
					Cast<ASpaceship>(actor)->GetHealthComponent()->RemoveLife(1);
				}
			}
		}
	}

}
