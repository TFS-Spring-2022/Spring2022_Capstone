// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "ShotgunWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API AShotgunWeapon : public AWeaponBase
{
	GENERATED_BODY()

	/**
	 * @brief Amount of raycasts fired in projecting cone.
	 */
	UPROPERTY(EditAnywhere, Category="Weapon Stats")
	int PelletCount; 
	
	/**	
	* @brief Fires a group of raycasts in a cone projecting from the player.
	*/
	UFUNCTION(BlueprintCallable)
	virtual void Shoot() override;
	
};
