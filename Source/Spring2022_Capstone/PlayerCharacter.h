// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class AWeaponBase;
class UInputMappingContext;
class UInputAction;
class UInputComponent;
class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UHealthComponent;

DECLARE_DELEGATE_OneParam(FOnHealthChanged, float);
DECLARE_DELEGATE(FOnGrappleActivated);
DECLARE_DELEGATE_OneParam(FOnGrappleCooldownStart, FTimerHandle&);
DECLARE_DELEGATE(FOnGrappleCooldownEnd);
UCLASS()
class SPRING2022_CAPSTONE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	FOnHealthChanged OnHealthChangedDelegate;
	FOnGrappleActivated OnGrappleActivatedDelegate;
	FOnGrappleCooldownStart OnGrappleCooldownStartDelegate;
	FOnGrappleCooldownEnd OnGrappleCooldownEndDelegate;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;
	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void CalcCamera(float DeltaTime, struct FMinimalViewInfo &OutResult) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputMappingContext *CharacterMappingContext;

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
	
	void Move(const FInputActionValue &Value);
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
	
	// Double Tap Time Handling on Dash
	float LastDashActionTappedTime = 0.0f;
	
	/**
	 * @brief Health Component
	 * @note Change health points using Set funtions
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

	UFUNCTION(BlueprintCallable)
	void TakeHit();

public:
	UFUNCTION()
	void GrappleDone();

	FTimerHandle handle;

	UFUNCTION(BlueprintCallable)
	void IncreaseMaxHealth(int Value);
	UFUNCTION(BlueprintCallable)
	void IncreaseMaxHealthPercentage(int Percentage);

	UFUNCTION(BlueprintCallable)
	void IncreaseMovementSpeed(int Value);

	UFUNCTION(BlueprintCallable)
	void IncreaseDamagePrimary(float Value);
	UFUNCTION(BlueprintCallable)
	void IncreaseDamageSecondary(float Value);

	UFUNCTION(BlueprintCallable)
	void ToggleDoubleJump();

	UFUNCTION(BlueprintCallable)
	void Heal(int Value);

	void HealByPercentage(int Percentage);
	float GetMaxHealth() const;

	// Sets Weapon references and sets to ActiveWeapon
	void SetWeapon1(AWeaponBase *Weapon);
	void SetWeapon2(AWeaponBase *Weapon);
	AWeaponBase *GetWeapon1() const;
	AWeaponBase *GetWeapon2() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Crouch)
	FVector CrouchEyeOffset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Crouch)
	float CrouchSpeed;
};
