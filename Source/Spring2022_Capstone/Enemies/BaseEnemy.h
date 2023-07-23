// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

class UBehaviorTree;
class UHealthComponent;
UCLASS(Abstract)
class SPRING2022_CAPSTONE_API ABaseEnemy : public ACharacter
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree *BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bDidHide;

	UFUNCTION(BlueprintCallable)
	virtual void Attack();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Damage;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float AttackSpeed;
};
