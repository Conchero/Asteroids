// Fill out your copyright notice in the Description page of Project Settings.


#include "../Entities/Spaceship.h"
#include "../Entities/AsteroidEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "../Arena.h"
#include "../../CustomComponents/TeleportationComponent.h"
#include "../../CustomComponents/ShootComponent.h"
#include "../../CustomComponents/HealthComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyEntity.h"
#include "../../CustomComponents/ShieldComponent.h"
#include "../Projectiles/Projectile.h"
#include "../../AsteroidGameMode.h"
#include "Materials/MaterialInstanceDynamic.h"

ASpaceship::ASpaceship()
{
	tpComponent = CreateDefaultSubobject<UTeleportationComponent>("tpComponent");
	shootComponent = CreateDefaultSubobject<UShootComponent>("shootComponent");

	shieldMesh = CreateDefaultSubobject<UStaticMeshComponent>("shieldMesh");
	shieldMesh->SetupAttachment(mesh);

	shieldComponent = CreateDefaultSubobject<UShieldComponent>("shieldComponent");
}

void ASpaceship::Revive()
{
	if (b_canRevive == true)
	{
		score = 0;
		b_canRevive = false;
		timerToRevive = timerToRevive;
		b_dead = false;
		GetHealthComponent()->AddLife(GetHealthComponent()->GetMaxHealth());
		SetActorHiddenInGame(false);
		boxCollider->SetGenerateOverlapEvents(true);
		SetUIGameOver(false);
		shieldComponent->ResetShield();
		shootComponent->SetNbShot(1);
		shootComponent->SetFireRate(shootComponent->GetBaseFireRate());
		GetWorld()->GetAuthGameMode<AAsteroidGameMode>()->ResetGame();
	}
}

void ASpaceship::Death()
{
	b_dead = true;
	shootComponent->OnFire(false);
	SetActorHiddenInGame(true);
	boxCollider->SetGenerateOverlapEvents(false);
	SetUIGameOver(true);
}

void ASpaceship::OnHealthChange()
{
	SetUIHealth();

	if (!GetHealthComponent()->GetCanTakeDamage())
	{
		shootComponent->SetFireRate(shootComponent->GetBaseFireRate());
	}
}

void ASpaceship::OnCanTakeDamageRestored()
{
	spaceshipDynMaterial->SetScalarParameterValue("Opacity", 1);
}

void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (!GetHealthComponent()->GetCanTakeDamage())
	{
		int moduloTimer = GetHealthComponent()->GetDamageCooldownTimer() *10;
		spaceshipDynMaterial->SetScalarParameterValue("Opacity", moduloTimer%2);
	}

	// here so the "any key" event in bp don't trigger instantly
	if ((b_dead == true || GetWorld()->GetAuthGameMode<AAsteroidGameMode>()->GetGameWin()) && b_canRevive == false)
	{
		timerToRevive -= DeltaTime;
		if (timerToRevive <= 0)
		{
			b_canRevive = true;
		}
	}
}

void ASpaceship::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(inputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpaceship::Move);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ASpaceship::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &ASpaceship::StopShoot);
		EnhancedInputComponent->BindAction(ShieldAction, ETriggerEvent::Started, this, &ASpaceship::ActivateShield);
		EnhancedInputComponent->BindAction(ShieldAction, ETriggerEvent::Completed, this, &ASpaceship::StopShield);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ASpaceship::Move(const FInputActionValue& Value)
{
	if (!GetIsDead())
	{
		// input is a Vector2D
		FVector2D MoveAxisVector = Value.Get<FVector2D>();

		if (Cast<APlayerController>(Controller) != nullptr)
		{
			AddMovementInput(GetActorForwardVector(), MoveAxisVector.X);
			AddMovementInput(GetActorRightVector(), MoveAxisVector.Y);
		}
	}
}

void ASpaceship::Shoot(const FInputActionValue& Value)
{
	if (!GetIsDead())
	{
		FVector2D ShootAxisVector = Value.Get<FVector2D>();
		FRotator newRotation = FRotator::ZeroRotator;

		int direction = 0;
		if (ShootAxisVector.X != 0)
		{
			direction = 90 * ShootAxisVector.X;
			newRotation = FRotator(GetMesh()->GetComponentRotation().Pitch, 90 * ShootAxisVector.X, GetMesh()->GetComponentRotation().Roll);
			GetMesh()->SetRelativeRotation(newRotation);
		}

		if (ShootAxisVector.Y != 0)
		{
			direction = (ShootAxisVector.Y == 1 ? 180 : 0);
			newRotation = FRotator(GetMesh()->GetComponentRotation().Pitch, direction, GetMesh()->GetComponentRotation().Roll);
			GetMesh()->SetRelativeRotation(newRotation);
		}

		shootComponent->OnFire(true, direction);
	}
}

void ASpaceship::StopShoot()
{
	shootComponent->OnFire(false);
}

void ASpaceship::ActivateShield()
{
	if (shieldComponent->GetIsAvailable())
	{
		shieldComponent->ActivateShield(shieldMesh);
	}
}

void ASpaceship::StopShield()
{
	if (shieldComponent->GetIsAvailable())
	{
		shieldComponent->DesactivateShield();
	}
}

void ASpaceship::BeginPlay()
{
	Super::BeginPlay();


	spaceshipDynMaterial = UMaterialInstanceDynamic::Create(mesh->GetMaterial(0),this);
	mesh->SetMaterial(0,spaceshipDynMaterial);

	timerToRevive = timerToReviveValue;

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (shieldComponent)
	{
		shieldComponent->SetHealthComponent(GetHealthComponent());
	}


	if (tpComponent)
	{
		AActor* arenaActor = nullptr;
		if (UGameplayStatics::GetActorOfClass(GetWorld(), AArena::StaticClass()))
			arenaActor = UGameplayStatics::GetActorOfClass(GetWorld(), AArena::StaticClass());

		if (arenaActor)
		{
			tpComponent->SetTrackedActor(arenaActor);

			if (Cast<AArena>(tpComponent->GetActorToTrack()))
			{
				AArena* castedArena = Cast<AArena>(tpComponent->GetActorToTrack());
				tpComponent->SetLimits(-castedArena->GetArenaWidth() / 2, castedArena->GetArenaWidth() / 2, -castedArena->GetArenaHeight() / 2, castedArena->GetArenaHeight() / 2);
			}
		}
	}

}
