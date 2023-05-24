// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "InventoryComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class SPRING2022_CAPSTONE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Functions allow character movement
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void StartCrouch();
	void StopCrouch();
	void StartSprint();
	void StopSprint();
	void Dash(FVector Direction);
	void DashEnd();
	void DashCoolDownEnd();
	UFUNCTION(BlueprintCallable)
	void Damage(float DamageValue);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthBar(float Percent);
	void Die();

	//Controls how fast the player can look around
	UPROPERTY(EditDefaultsOnly)
		float LookRate;

	//Camera to view the scene
	UPROPERTY(EditDefaultsOnly)
		UCameraComponent* PlayerCamera;

	UPROPERTY(EditDefaultsOnly)
		UInventoryComponent* InventoryComponent;
	
	UPROPERTY(EditDefaultsOnly)
		FVector StandingCameraRelativeLocation;
	
	UPROPERTY(EditDefaultsOnly)
		FVector CrouchingCameraRelativeLocation;

	UPROPERTY(EditDefaultsOnly)
		float WalkingSpeed;

	UPROPERTY(EditDefaultsOnly)
		float SprintingSpeed;

	UPROPERTY()
		bool bIsSprinting;

	UPROPERTY(EditDefaultsOnly)
		float DashStrength;

	UPROPERTY()
		FTimerHandle DashTimerHandle;

	UPROPERTY()
		FTimerHandle DashCoolDownTimerHandle;

	UPROPERTY(EditDefaultsOnly)
		float DashTime;

	UPROPERTY(EditDefaultsOnly)
		float DashCoolDownTime;

	UPROPERTY()
		bool bIsDashing;

	UPROPERTY()
		bool bIsDashOnCoolDown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float MaxHealth;

	UPROPERTY()
		bool bIsDead;
};
