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

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	bool bIsCharging;
	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UNiagaraComponent* LaserComponent;
    UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
    TSubclassOf<ABaseEnemyProjectile> Projectile;

public:

	void DisableSniperEnemy();

	void EnableSniperEnemy();


};
