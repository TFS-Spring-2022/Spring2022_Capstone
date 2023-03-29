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
UCLASS()
class SPRING2022_CAPSTONE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

	FOnHealthChanged OnHealthChangedDelegate;

	// Sets Weapon references and sets to ActiveWeapon
	void SetWeapon1(AWeaponBase *Weapon);
	void SetWeapon2(AWeaponBase *Weapon);
	AWeaponBase *GetWeapon1() const;
	AWeaponBase *GetWeapon2() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputMappingContext *CharacterMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction *MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction *LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *JumpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *SprintAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *CrouchAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *GrapleAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *AttackAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *SwitchWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UHealthComponent *PlayerHealthComponent;

	void Move(const FInputActionValue &Value);
	void Look(const FInputActionValue &Value);

	void Attack(const FInputActionValue &Value);
	// Switches ActiveWeapon between Weapon1 and Weapon2
	void SwitchWeapon(const FInputActionValue &Value);
	void Sprint(const FInputActionValue &Value);
	void Crouch(const FInputActionValue &Value);

	UFUNCTION(BlueprintCallable)
	void TakeHit();

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
};
