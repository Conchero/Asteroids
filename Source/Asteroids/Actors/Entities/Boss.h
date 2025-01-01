// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Entities/EnemyEntity.h"
#include "../../Enums/EBossShootPattern.h"
#include "Boss.generated.h"

/**
 *
 */
UCLASS()
class ASTEROIDS_API ABoss : public AEnemyEntity
{
	GENERATED_BODY()

	ABoss();

public:
	virtual void Death() override;
	virtual void OnHealthChange() override;
	virtual void OnCanTakeDamageRestored() override;


	void BossKilled();
	void RemoveFromArena();

	void ResetEyeBeamMeshAndMaterial();
	void SetEyeBeamActivated(bool _b) ;

	int CheckPlayerPresence();

	class UStaticMeshComponent* GetEyeBeamMesh() {return eyeBeamMesh;};

	class UMaterialInstanceDynamic* GetEyeBeamMaterial() {return eyeBeamDynMaterial;};

	void SetMoveCannon(bool _b);
	class ABossCannon* GetRightCannon() { return bossRightCannon; };
	class ABossCannon* GetLeftCannon() {return bossLeftCannon;};

	TArray<int> GetPartsAlive();

protected:

	bool CheckPlayerBossEyeRaycast();

	UPROPERTY(EditAnywhere)
	int eyeWidth = 100;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABossCannon> bossRightCannonRef;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABossCannon> bossLeftCannonRef;

	class ABossCannon* bossRightCannon;
	class ABossCannon* bossLeftCannon;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBehaviorTreeComponent* behaviorTree;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* eyeBeamMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* eyeBeamCollider;

	bool eyeBeamActivated = false;

	class UMaterialInstanceDynamic* eyeBeamDynMaterial;
	class UMaterialInstanceDynamic* eyeDynMaterial;


	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere)
	int cannonDistanceFromEye = 200;

	FLinearColor baseEyeBeamColor;
	float baseEyeBeamOpacity;
	FVector baseEyeBeamScale;

};
