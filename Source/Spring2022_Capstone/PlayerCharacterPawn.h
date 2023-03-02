// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacterPawn.h"
#include "InputActionValue.h"
#include "PlayerCharacterPawn.generated.h"

class UInputMappingContext;
class UInputAction;
class UInputComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SPRING2022_CAPSTONE_API APlayerCharacterPawn : public ABaseCharacterPawn
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

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPawnMovementComponent> MovementComponent;

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
