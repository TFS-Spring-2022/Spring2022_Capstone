// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class SPRING2022_CAPSTONE_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	
	//// Weapon Stats

	// Current weapon charge (ammo) percentage.
	UPROPERTY(EditAnywhere, Category="Weapon Stats")
		float CurWeaponCharge = 0;

	// Weapon charge cost per shot.
	UPROPERTY(EditAnywhere, Category="Weapon Stats")
		float ShotCost = 10;

	// Weapon Cooldown rate (-charge per second).
	UPROPERTY(EditAnywhere, Category="Weapon Stats")
		float ChargeCooldownRate = 5;

	// Time it takes for the weapon to finish overheating.
	UPROPERTY(EditAnywhere, Category="Weapon Stats")
		float OverheatTime = 5.0f;

	// ToDo: Damage not implemented 
	UPROPERTY(EditAnywhere, Category="Weapon Stats")
		float ShotDamage = 35;

	// Time between shots (seconds).
	UPROPERTY(EditAnywhere, Category="Weapon Stats")
		float FireRate = .5;

	// ToDo: Pick a general size when we get a better idea of level size
	// Distance the raycast shot travels.
	float ShotDistance = 10000.0f;

	
	//// Weapon Runtime

	bool bIsOverheating = false;
	bool bCanFire = true;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * @brief Fires a single raycast shot forwards from the camera.
	 */
	UFUNCTION(BlueprintCallable)
		void RaycastFire();
	
	/**
	 * @brief Subtract 'ChargeCooldownRate' from 'CurWeaponCharge' once every second (Uses 'MemberTimeHandle' set in BeginPlay()).
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

	void ClearFireTimerHandle();

	// Timer used to handle seconds between shots.
	FTimerHandle FireTimerHandle;

	// Timer to handle the time spent in overheat mode.
	FTimerHandle OverheatTimerHandle;

	// Timer to handle the charge cooldown per second.
	FTimerHandle ChargeCooldownTimerHandle;

	UPROPERTY()
		APlayerCameraManager* PlayerCamera; 

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* SkeletalMesh;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	/**
	 * @brief The character holding the weapon
	 */
	APlayerCharacter* Character;

public:
	// ToDo: I think we can get rid of Tick [PrimaryActorTick.bCanEverTick = true;]
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/**
	 * @brief Attaches the actor to a PlayerCharacter.
	 * @param TargetCharacter APlayerCharacter instance holding the actor.
	 */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(APlayerCharacter* TargetCharacter);

	// Fire Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon", meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UInputMappingContext *CharacterMappingContext;

};
