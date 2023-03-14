// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "BaseCharacterPawn.generated.h"

UCLASS()
class SPRING2022_CAPSTONE_API ABaseCharacterPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseCharacterPawn();

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

	//Controls how fast the player can look around
	UPROPERTY(EditDefaultsOnly)
	float LookRate;

	//Camera to view the scene
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;

};
