// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "SniperEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API ASniperEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
protected:
	void Attack() override;

	UFUNCTION(BlueprintCallable)
	void SpecialAttack();
	UFUNCTION(BlueprintCallable)
	void StartCharge();
	UFUNCTION(BlueprintCallable)
	void StopCharge();
	
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float ChargeTime;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	bool bIsCharging;
};
