// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Spring2022_Capstone/Weapon/WeaponBase.h"
#include "UpgradeSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Within=(PlayerCharacter))
class SPRING2022_CAPSTONE_API UUpgradeSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUpgradeSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/**
	 * @brief Increases given weapon's MaxChargeAmount by IncrementAmount.
	 * @param WeaponToUpgrade  WeaponBase child to be changed.
	 * @param IncrementAmount Amount added to give weapon's MaxChargeAmount.
	 */
	UFUNCTION(BlueprintCallable)
		void IncreaseMaxChargeAmount(AWeaponBase* WeaponToUpgrade, float IncrementAmount);

	/**
	 * @brief Increases the given APlayerCharacter's max health by a float amount.
	 * @param Character APlayerCharacter child to be changed.
	 * @param IncrementAmount Amount to be added to Character's Max Health.
	 */
	UFUNCTION(BlueprintCallable)
		void IncreaseMaxHealthByAmount(APlayerCharacter* Character, float IncrementAmount);
	
	/**
	 * @brief Increases the given APlayerCharacter's max health by a percentage.
	 * @param Character PlayerCharacter child to be changed.
	 * @param PercentageAmount Percentage of health to be added to Character's Max Health.
	 */
	UFUNCTION(BlueprintCallable)
		void IncreaseMaxHealthByPercentage(APlayerCharacter* Character, float PercentageAmount);
	
};
