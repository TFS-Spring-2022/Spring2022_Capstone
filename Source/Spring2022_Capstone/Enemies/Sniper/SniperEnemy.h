// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Spring2022_Capstone/Enemies/BaseEnemy.h"
#include "SniperEnemy.generated.h"

class UNiagaraComponent;
class ABaseEnemyProjectile;

UCLASS()
class SPRING2022_CAPSTONE_API ASniperEnemy : public ABaseEnemy
{
	GENERATED_BODY()

	ASniperEnemy();

protected:

	virtual void Tick(float DeltaTime) override;
	
	virtual void BeginPlay() override;
    
	virtual void Attack() override;

	bool bCanAttack = true;
	
	UFUNCTION(BlueprintCallable)
	void SpecialAttack();
	UFUNCTION(BlueprintCallable)
	void StartCharge();
	UFUNCTION(BlueprintCallable)
	void StopCharge();
	UFUNCTION(BlueprintCallable)
	void LockOn();
	UFUNCTION(BlueprintCallable)
	void Reload();

	FTimerHandle TimeBeforeShotTimerHandler;
	FTimerHandle ReloadTimerHandler;

	float Range = 10000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	bool bIsCharging;
	
	float chargeTime;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UNiagaraComponent* LaserComponent;
    UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
    TSubclassOf<ABaseEnemyProjectile> Projectile;

public:

	void DisableSniperEnemy();

	void EnableSniperEnemy();

	UPROPERTY()
	bool bIsDisabled = false;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsDisabled() {return bIsDisabled;}

	FTimerHandle RagdollTimerHandle;
	float TimeBeforeRagdoll = 6.0f;
	
	UFUNCTION()
	void DelayRagdoll();


};
