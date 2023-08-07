// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class APlayerCharacter;

UCLASS(Abstract)
class SPRING2022_CAPSTONE_API AWeaponBase : public AActor
{
	GENERATED_BODY()

	friend class UUpgradeSystemComponent;
	friend class URecoilComponent;
		
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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void PlayWeaponCameraShake();
	
	//// Weapon Stats

	// Current weapon charge (ammo).
	UPROPERTY(EditAnywhere, Category="Weapon Stats")
		float CurrentCharge = 0;

	// Max weapon charge amoutn before overheating
	UPROPERTY(EditAnywhere, Category="Weapon Stats")
		float MaxChargeAmount = 100;

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

	/**
	 * @brief Calls ChangeCrosshair() from PlayerCharacter.
	 */
	void ShowHitMarker();
	
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
	APlayerCharacter* PlayerCharacter;

	UPROPERTY()
	APlayerCameraManager* PlayerCamera; 

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<UCameraShakeBase> FireCameraShake;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	UTexture2D* WeaponIcon;

public:
	// ToDo: I think we can get rid of Tick [PrimaryActorTick.bCanEverTick = true;]
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetDamage();
	void SetDamage(float Value);

	float GetCurrentCharge() const;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTexture2D* GetWeaponIcon() {if(WeaponIcon) return WeaponIcon; else return nullptr;}
	
};
