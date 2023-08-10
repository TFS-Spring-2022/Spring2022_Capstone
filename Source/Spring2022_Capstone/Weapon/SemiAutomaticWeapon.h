// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "RecoilComponent.h"
#include "DamageNumberWidget.h"
#include "WeaponBase.h"
#include "SemiAutomaticWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API ASemiAutomaticWeapon : public AWeaponBase
{
	GENERATED_BODY()

	ASemiAutomaticWeapon();
	
	/**	
	 * @brief Fires a single raycast shot forwards from the camera.
	*/
	UFUNCTION(BlueprintCallable)
	virtual void Shoot() override;

	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageNumberWidget> DamageNumberWidgetClass;

	UPROPERTY(EditAnywhere)
	URecoilComponent* RecoilComponent;
	
};
