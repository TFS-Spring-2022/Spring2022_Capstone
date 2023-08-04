// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "AttackSystemAgentInterface.h"
#include "GameFramework/Character.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "BaseEnemy.generated.h"

class UBehaviorTree;
class UHealthComponent;
UCLASS(Abstract)
class SPRING2022_CAPSTONE_API ABaseEnemy : public ACharacter, public IDamageableActor, public IAttackSystemAgentInterface
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
	virtual void Attack();
	
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

	// Called from the AttackSystem to set bHasAttackToken true;
	virtual void ReceiveToken() override;

	// Called to set bHasAttackToken false and return logical token to Attack System Component.
	virtual void ReleaseToken() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Damage;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float AttackSpeed;

	UPROPERTY()
	APlayerCharacter* PlayerCharacter;

	// This enemy is holding the AI Attack System Component's logical token to
	// allow the holder's shot to hit the target.
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bHasAttackToken = false;



	UPROPERTY()
	class UAIAttackSystemComponent* CurrentAttackSystemComponent;
	
};
