// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Components/ActorComponent.h"
#include "RecoilHelper.generated.h"

/// Handles recoil for parent weapons.
/// @warning - Can only be added to AWeaponBase and children. 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Within=(WeaponBase))
class SPRING2022_CAPSTONE_API URecoilHelper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecoilHelper();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Called on a weapon's fire. Begins the process of moving
	 * the player's aim and resetting on rest.
	 */
	void RecoilStart();

private:
	
	/**
	 * @brief WeaponBase the RecoilHelper component is attached to. 
	 */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	AWeaponBase* OwningParentWeapon; 

	UPROPERTY(VisibleAnywhere, Category = "Components")
	APlayerController* OwnersPlayerController;

	/**
	 * @brief Amount of vertical movement on each shot.
	 */
	UPROPERTY(EditAnywhere, Category = "Properties")
	float VerticalKickAmount;

	/**
	* @brief Time before aim recovery begins.
	* @note 0.5 feels nice.
	*/
	UPROPERTY(EditAnywhere, Category = "Properties") 
	float TimeBeforeRecovery = 0.5;
	
	/**
	* @brief The speed the recoil recovers at
	* @note 25 as a default feels good.
	*/
	UPROPERTY(EditAnywhere, Category = "Properties")
	float RecoverySpeed = 25.0f;
	
// Aim Rotators //
	// Control rotation at the start of the recoil
	UPROPERTY() 
	FRotator RecoilStartRot;
	
	// Control rotation change due to recoil
	UPROPERTY() 
	FRotator RecoilDeltaRot;

	// Control rotation change due to mouse movement
	UPROPERTY() 
	FRotator PlayerDeltaRot;
	
	UPROPERTY() 
	FRotator Del;

	
// Runtime Variables //
	bool bIsFiring;
	
	bool bRecoil;
	
	bool bRecoilRecovery;
	
	bool bOriginalAimRotSet;

	
// Timer Handles & Functions //
	FTimerHandle RecoveryTimerHandle;
	UFUNCTION()
	void RecoveryTimerFunction();

	FTimerHandle FireTimerHandle;
	UFUNCTION()
	void RecoilTimerFunction();

	FTimerHandle TimeSinceLastShotTimerHandle;
	// Called when firing stops, no need to call directly
	UFUNCTION() 
	void RecoilStop();
	
	
	// This function is called inside Tick, no need to call directly.
	void RecoveryStart();
	
};
