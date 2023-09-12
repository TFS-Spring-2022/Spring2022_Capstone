// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "RangedEnemy.generated.h"

class ABaseEnemyProjectile;

UCLASS()
class SPRING2022_CAPSTONE_API ARangedEnemy : public ABaseEnemy
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void SpecialAttack();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
	TSubclassOf<ABaseEnemyProjectile> Projectile;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	int MagazineSize;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	int Ammo;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float ReloadTime;

	void Reload();
};
