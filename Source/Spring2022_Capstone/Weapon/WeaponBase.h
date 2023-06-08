// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"


DECLARE_DELEGATE_OneParam(FOnWeaponChargeChanged, float);
DECLARE_DELEGATE_OneParam(FOnWeaponOverheatChanged, bool);

UCLASS(Abstract)
class SPRING2022_CAPSTONE_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	/**
	* @brief Attaches the actor to a PlayerCharacter.
	* @param TargetCharacter APlayerCharacter instance holding the actor.
	*/
	UFUNCTION(BlueprintCallable, Category="Equip")
	void AttachWeapon(APlayerCharacter* TargetCharacter);

	virtual void Shoot() PURE_VIRTUAL(AWeaponBase::Shoot());
	
	FOnWeaponChargeChanged OnWeaponChargeChangedDelegate;
	FOnWeaponOverheatChanged OnWeaponOverheatChangedDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//// Weapon Stats

	// Current weapon charge (ammo) percentage.
	UPROPERTY(EditDefaultsOnly, Category="Weapon Stats")
		float CurWeaponCharge = 0;

	// Weapon charge cost per shot.
	UPROPERTY(EditDefaultsOnly, Category="Weapon Stats")
		float ShotCost = 10;

	// Weapon Cooldown rate (-charge per second).
	UPROPERTY(EditDefaultsOnly, Category="Weapon Stats")
		float ChargeCooldownRate = 5;

	// Time it takes for the weapon to finish overheating.
	UPROPERTY(EditDefaultsOnly, Category="Weapon Stats")
		float OverheatTime = 5.0f;

	// ToDo: Damage not implemented 
	UPROPERTY(EditDefaultsOnly, Category="Weapon Stats")
		float ShotDamage = 35;

	// Time between shots (seconds).
	UPROPERTY(EditDefaultsOnly, Category="Weapon Stats")
		float FireRate = .5;

	// ToDo: Pick a general size when we get a better idea of level size
	// Distance the raycast shot travels.
	float ShotDistance = 10000.0f;

	
	//// Weapon Runtime

	bool bIsOverheating = false;
	bool bCanFire = true;
	
	/**
	 * @brief Subtracts 'ChargeCooldownRate' from 'CurWeaponCharge' once every second (Uses 'MemberTimeHandle' set in BeginPlay()).
	 */
	void ChargeCooldown();

	/**
	 * @brief Disables firing and marks weapon overheating for set time.
	 * @note Weapon is disabled for 'OverheatTime'.
	 */
	void Overheat();

	/**
	 * @brief Re-enables weapon firing.
	 * @note Called from ChargeCooldown() after 'OverheatTime' has elapsed.
	 */
	void WeaponCooldown();
	
	// Timer used to handle seconds between shots.
	FTimerHandle FireTimerHandle;

	// Timer to handle the time spent in overheat mode.
	FTimerHandle OverheatTimerHandle;

	// Timer to handle the charge cooldown per second.
	FTimerHandle ChargeCooldownTimerHandle;

	void ClearFireTimerHandle();

	
	//// Components
	
	/**
	 * @brief The character holding the weapon.
	 */
	UPROPERTY()
	APlayerCharacter* Character;

	UPROPERTY()
	APlayerCameraManager* PlayerCamera; 

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;

public:
	// ToDo: I think we can get rid of Tick [PrimaryActorTick.bCanEverTick = true;]
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetDamage();
	void SetDamage(float Value);
	
};
