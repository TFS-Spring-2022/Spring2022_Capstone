// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Components/ActorComponent.h"
#include "RecoilComponent.generated.h"

/// Handles recoil for parent weapons.
/// @warning - Can only be added to AWeaponBase and children. 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Within=(WeaponBase))
class SPRING2022_CAPSTONE_API URecoilComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecoilComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when a weapon is fired to begin the recoil process.
	void RecoilKick();

private:

	// Recover the Player's Control Rotation while taking mouse movement into account. 
	void RecoverRecoil(float Time);

	// Resets all properties used in the recoil process.
	UFUNCTION()
	void RecoilReset();
	
// Components
	// WeaponBase the RecoilComponent is attached to.
	UPROPERTY()
	AWeaponBase* OwningParentWeapon; 

	// Player Controller handling weapon.
	UPROPERTY()
	APlayerController* OwnersPlayerController;

	// Movement Component of Player handling weapon.
	UPROPERTY()
	UPawnMovementComponent* OwnersPawnMovementComponent;

// Rotators
	// Player's Control Rotation at the start of recoil.
	FRotator RecoilStartRotation;
	
	// Used to calculate Player Control Rotation's pitch after vertical kick.
	FRotator RecoilRotation;

	// Used to calculate Player Control Rotation's pitch while taking Player's mouse movement into account. 
	FRotator RecoveryRotation;

	// Temporary Rotator used to recover Player's Control Rotation.
	FRotator CorrectionRotation;

// Properties
	/**
	 * @brief Used to handle recoil on weapon's with larger fire rates ( > 0.5).
	 * Sets a specific FireTimerHandle length and RecoilRecoveryTimer so player's do not
	 * lose control of their aim. Set inside BeginPlay().
	 */
	bool bHasLargerFireRate;

	/**
	 * @brief Amount the Player's Control Rotation will be forced upwards on a shot.
	 */
	UPROPERTY(EditAnywhere, meta=(ClampMin = " -89.9", ClampMax = "0"), Category = "Recoil | Properties")
	float VerticalKickAmount;

	// Speed the Player's Control Rotation is moved during recoil recovery.
	UPROPERTY(EditAnywhere, Category = "Recoil | Properties")
	float RecoverySpeed = 10.0f;

// Runtime
	bool bIsRecoiling;
	bool bIsRecovering;

	// Number of shots fired in current batch.
	int TimesFired;

	// The amount Player's Control Rotation needs to be brought down vertically during recoil recovery.
	float PitchRecoveryAmount;

// Timers
	// Used to start recoil recovery after player has finished shooting.
	FTimerHandle FireTimerHandle;

	// Called automatically from RecoilKick(), no need to call directly.
	UFUNCTION()
	void FireTimerHandleFunction();

	// Used to cancel recovery if given time has passed to prevent Player losing control.
	FTimerHandle BackupRecoveryTimer;
	
// Const Variables
	const float LargeFireRateSize = 0.5f;						// Fire rates larger then this size are considered large.
	const float FireTimeBuffer = 0.20f;							// Buffer used in FireTimer to check if the player is still firing.
	const float SemiAutomaticMaxTimeInRecoveryBuffer = 0.005f;	// Added to a weapon's fire rate to set the max time(s) a semi automatic can be spent recovering. Used ot ensure player does not lose control.
	const float LargeFireRateMaxTimeInRecovery = 0.10f;			// The max time(s) a weapon with large fire rate (i.e. Shotgun) can be spent recovering. Used to ensure player does not lose control.
	const float LargeFireRateRecoveryStartTime = 0.19f;			// Time(s) before recoil recovery starts with a large fire rate weapon.
	const float RecoilRecoveryTolerance = 0.005f;				// Used when comparing Player's current rotation to recovery rotation point to check if finished.
	
};
