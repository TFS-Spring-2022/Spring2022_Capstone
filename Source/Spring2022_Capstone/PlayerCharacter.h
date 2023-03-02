// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UInputComponent;
class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;

UCLASS()
class SPRING2022_CAPSTONE_API APlayerCharacterPawn : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacterPawn();

	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputMappingContext *CharacterMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction *MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction *LookAction;

	void Move(const FInputActionValue &Value);
	void Look(const FInputActionValue &Value);

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	UCameraComponent *Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 200.f;
};
