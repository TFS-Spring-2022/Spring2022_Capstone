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

UCLASS()
class SPRING2022_CAPSTONE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputMappingContext *CharacterMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction *MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction *LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *GrapleAction;

	void Move(const FInputActionValue &Value);
	void Look(const FInputActionValue &Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UCameraComponent *Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 200.f;
};
