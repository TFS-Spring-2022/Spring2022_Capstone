// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "RecoilComponent.h"
#include "WeaponBase.h"
#include "ShotgunWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API AShotgunWeapon : public AWeaponBase
{
	GENERATED_BODY()

	AShotgunWeapon();

	/**
	 * @brief Amount of raycasts fired in projecting cone.
	 */
	UPROPERTY(EditAnywhere, Category="Weapon Stats")
	int PelletCount; 
	
	/**	
	* @brief Fires a group of raycasts in a cone projecting from the player.
	*/
	UFUNCTION(BlueprintCallable)
	virtual bool Shoot() override;

	UPROPERTY(EditAnywhere)
	URecoilComponent* RecoilComponent;

	// Used to prevent multiple calls to ShowHitMarker() when multiple pellets hit.
	bool bPelletConnected = false;
	
};
