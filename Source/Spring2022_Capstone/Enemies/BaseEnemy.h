// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"
#include "BaseEnemy.generated.h"

class UBehaviorTree;
class UHealthComponent;
UCLASS(Abstract)
class SPRING2022_CAPSTONE_API ABaseEnemy : public ACharacter, public IDamageableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent *WeaponMesh;
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	USceneComponent *ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	UHealthComponent *HealthComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree *BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bDidHide;

	UFUNCTION(BlueprintCallable)
	virtual void AttackHit();

	UFUNCTION(BlueprintCallable)
	virtual void AttackMiss();
	
	// Called when the enemy runs out of health. Removes enemy from WaveManager ActiveEnemies[] and destroys itself.
	UFUNCTION(BlueprintCallable)
	void Death();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void DamageActor(AActor* DamagingActor, const float DamageAmount) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Damage;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float AttackSpeed;
	
};
