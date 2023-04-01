// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "RangedEnemy.generated.h"

class URangedWeapon;

/**
 *
 */
UCLASS()
class SPRING2022_CAPSTONE_API ARangedEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARangedEnemy();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	URangedWeapon *Weapon;
};
