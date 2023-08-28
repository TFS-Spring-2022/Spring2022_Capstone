// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "AttackSystemAgentInterface.h"
#include "GameFramework/Character.h"
#include "Spring2022_Capstone/BasePickup.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "BaseEnemy.generated.h"

USTRUCT()
struct FEnemyDrop
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePickup> EnemyDrop;

	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 0, ClampMax = 100));
	float DropChancePercentage = 0;
};

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
	
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	UTextRenderComponent* NameTextRenderer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	UHealthComponent *HealthComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree *BehaviorTree;
	
	UPROPERTY(EditDefaultsOnly, Category = "Drops", meta = (AllowPrivateAccess = true))
	TArray<FEnemyDrop> Drops;

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
	virtual void DamageActor(AActor* DamagingActor, const float DamageAmount, FName HitBoneName = "NONE") override;

	// Called from the AttackSystem to set bHasAttackToken true;
	virtual void ReceiveToken() override;

	// Called to set bHasAttackToken false and return logical token to Attack System Component.
	virtual void ReleaseToken() override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsFiring() {return bIsFiring;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetIsFiring(bool NewState) {bIsFiring = NewState;}
	
	// Plays a section in an anim montage holding all hit animations inside the enemy's blueprint.
	UFUNCTION(BlueprintImplementableEvent)
	void PlayHitAnimation(FName HitBone);

	void PromoteToElite();

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
	
	UPROPERTY(EditAnywhere, Category = "Animation")
	bool bIsFiring;

	UPROPERTY(EditAnywhere, Category = "Components")
	TArray<UMaterial*> EnemyColors;

	const FName WeaponSocket = "Grunt_RightHand_Pistol"; // Socket that holds the enemies weapon.
	const float NameTextRenderVerticalBuffer = 20.0f; // Number subtracted from NameTextRenderer's vertical position.
	
};
