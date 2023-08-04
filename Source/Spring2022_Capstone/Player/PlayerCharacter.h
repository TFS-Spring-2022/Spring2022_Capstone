// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MantleSystemComponent.h"
#include "UpgradeSystemComponent.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"
#include "Spring2022_Capstone/UI/HUD/DirectionalDamageIndicatorWidget.h"
#include "Spring2022_Capstone/UI/HUD/HUDWidget.h"
#include "PlayerCharacter.generated.h"

class AWeaponBase;
class UInputMappingContext;
class UInputAction;
class UInputComponent;
class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UHealthComponent;
class UGrappleComponent;

DECLARE_DELEGATE_OneParam(FOnHealthChanged, float);
DECLARE_DELEGATE(FOnDamaged);

UCLASS()
class SPRING2022_CAPSTONE_API APlayerCharacter : public ACharacter, public IDamageableActor
{
	GENERATED_BODY()

	friend class UUpgradeSystemComponent;

public:
	APlayerCharacter();

	FOnHealthChanged OnHealthChangedDelegate;
	FOnDamaged OnDamagedDelegate;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;
	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void CalcCamera(float DeltaTime, struct FMinimalViewInfo &OutResult) override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Upgrades")
	UUpgradeSystemComponent* UpgradeSystemComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputMappingContext *CharacterMappingContext;

	//// HUD Related
	
	//Player HUD
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> PlayerHUDWidgetBP;

	UPROPERTY()
	UHUDWidget* PlayerHUDWidgetInstance;
	
	// Directional Damage UUSerWidget To Create.
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> DamageIndicatorWidgetBP;
	
	UPROPERTY()
	UDirectionalDamageIndicatorWidget* DirectionalDamageIndicatorWidget;
	

	////	MOVEMENT RELATED INPUT ACTIONS
	/**
	 * @brief Holds the Move Input Action
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction *MoveAction;
	/**
	 * @brief Holds the Look Input Action
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction *LookAction;
	/**
	 * @brief Holds the Jump Input Action
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *JumpAction;
	/**
	 * @brief Holds the Sprint Input Action
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *SprintAction;
	/**
	 * @brief Holds the Crouch Input Action
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *CrouchAction;

	////	CASTING AND ATTACK RELATED INPUT ACTIONS
	/**
	 * @brief Holds the Grapple Input Action
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *GrappleAction;
	/**
	 * @brief Holds the Attack Input Action
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *AttackAction;
	/**
	 * @brief Holds the Switch Weapons Input Action
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *SwitchWeaponAction;
	/**
	 * @brief Holds the Dash Input Action 
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UGrappleComponent *GrappleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UMantleSystemComponent* PlayerMantleSystemComponent;
	
	void Move(const FInputActionValue &Value);
	virtual void Jump() override;
	
	void Dash(const FInputActionValue &Value);
	void Look(const FInputActionValue &Value);
	void Sprint(const FInputActionValue &Value);
	void Crouch(const FInputActionValue &Value);
	void Attack(const FInputActionValue &Value);
	void Grapple(const FInputActionValue &Value);
	// Switches ActiveWeapon between Weapon1 and Weapon2
	void SwitchWeapon(const FInputActionValue &Value);

	// Time between presses of a button to indicate a double tap
	UPROPERTY(EditAnywhere, Category = "Input")
	float DoubleTapActivationDelay = 0.5f;

// Dash Mechanic Runtime
	bool bCanDash = true;
	
	// Double Tap Time Handling on Dash
	float LastDashActionTappedTime = 0.0f;

	// Used to check for double press of same button
	float PreviousDashDirection;

	UPROPERTY(EditAnywhere)
	float DashDistance = 1250;

	// Used with DashCoolDownTime to handle cooldown
	FTimerHandle DashCooldownTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<UCameraShakeBase> DashCameraShake;

	/**
	* @brief Dash cooldown in seconds
	*/
	UPROPERTY(EditAnywhere, Category = "Movement")
	float DashCooldownTime;
	
	/**
	 * @brief Sets bCanDash back to true
	 * @note Called automatically from Dash()
	 */
	UFUNCTION()
	void ResetDashCooldown();

	// Used to handle the delay after initial knock-up in Dash()
	FTimerHandle DashDirectionalMovementDelayTimerHandle;

	/**
	 * @brief Dashes the Actor in the desired direction
	 * @note Called automatically from Dash() after a tiny delay.
	 */
	UFUNCTION()
	void DashDirectionalLaunch();

	/**
	 * @brief The InputValue used in the dash's direction.
	 * @note Set in Dash() and used in DashDirectionLaunch
	 */
	FVector2D DashDirectionalValue;

	/// Dash 
	FTimerHandle DashBlurTimerHandle;

	// Time dash blur post process effect will remain on screen. (0.3).
	UPROPERTY(EditAnywhere)
	float DashBlurUpTime;

	bool bDashBlurFadingIn;

	/**
	 * @brief Sets post process blur effect weight to 0. Turning off
	 * the effect. Called automatically for Timer set in Dash().
	 */
	UFUNCTION()
	void ClearDashBlur();

	float const DASH_BLUR_FADEIN_SPEED = 0.060; // FInterpTo speed used to fade in dash blur post process effect.

	
	/**
	 * @brief Health Component
	 * @note Change health points using Set functions
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UHealthComponent *HealthComponent;
	
	void UpdateHealthBar();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UCameraComponent *Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Acceleration = 200.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintMultiplier = 1.2f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 200.f;

	// ToDo: Currently assigned inside WeaponBase::BeginPlay() from weapons in level.
	UPROPERTY(EditAnywhere, Category = "Player Inventory")
	AWeaponBase *Weapon1;

	UPROPERTY(EditAnywhere, Category = "Player Inventory")
	AWeaponBase *Weapon2;

	// Player's current weapon. Will be used on Attack()
	UPROPERTY(VisibleAnywhere, Category = "Player Inventory")
	AWeaponBase *ActiveWeapon;

	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bIsSprinting;

	bool bIsMoving;

	bool bIsMantleing;

	bool bIsSwappingWeapon = false;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsSwapping() {return bIsSwappingWeapon;}

	FTimerHandle IsSwappingTimerHandle;

	UFUNCTION()
	FORCEINLINE void ToggleIsSwappingOff() {bIsSwappingWeapon = false;}

public:
	
	UFUNCTION(BlueprintCallable)
	void Heal(int Value);

	void HealByPercentage(int Percentage);
	float GetMaxHealth() const;
	UGrappleComponent* GetGrappleComponent();

	// Sets Weapon references and sets to ActiveWeapon
	void SetWeapon1(AWeaponBase *Weapon);
	void SetWeapon2(AWeaponBase *Weapon);
	AWeaponBase *GetWeapon1() const;
	AWeaponBase *GetWeapon2() const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Crouch)
	FVector CrouchEyeOffset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Crouch)
	float CrouchSpeed;

	void SetIsMantleing(bool IsMantleingStatus);

	FORCEINLINE UHUDWidget* GetPlayerHUD() {return PlayerHUDWidgetInstance;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AWeaponBase* GetActiveWeapon() {return ActiveWeapon;}

	UFUNCTION(BlueprintCallable)
	virtual void DamageActor(AActor* DamagingActor, const float DamageAmount) override;

	// ToDo: Handle Grapple Indicator in here
	void ChangeCrosshair();
	
	float const GRAPPLE_TRACE_START_FORWARD_BUFFER = 65.0f; // Used to start grapple trace in front of Player and not collide with skeletal mesh.
	
	// NOTE - Temporarily using to call GameMode's SpawnWave() from player bp.
	UFUNCTION(BlueprintCallable)
	void DEBUG_SpawnWave();

	UUpgradeSystemComponent* GetUpgradeSystemComponent();

	FORCEINLINE bool GetIsSprinting() const {return bIsSprinting;}
	
};
