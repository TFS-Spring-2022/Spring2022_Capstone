// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "SniperEnemy.generated.h"

class UNiagaraComponent;

UCLASS()
class SPRING2022_CAPSTONE_API ASniperEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	ASniperEnemy();
	
	virtual void Tick(float DeltaTime) override;
	
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
	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UNiagaraComponent* LaserComponent;
};
