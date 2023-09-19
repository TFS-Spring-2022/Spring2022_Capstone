// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplaySystems/EnemyWaveManagementSystem.h"
#include "Player/PlayerCharacter.h"
#include "Spring2022_CapstoneGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API ASpring2022_CapstoneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	// The Enemy Wave Manager BP for the level.
	UPROPERTY(EditDefaultsOnly, Category = "Wave Management")
	TSubclassOf<UEnemyWaveManagementSystem> LevelEnemyWaveManagerBP;

	// An instance of the LevelEnemyWaveManagerBP.
	UPROPERTY(VisibleAnywhere, Category = "Wave Management")
	UEnemyWaveManagementSystem* EnemyWaveManagerInstance;

	UPROPERTY()
	USoundManagerSubSystem* SoundManagerSubSystem;

	APlayerCharacter* PlayerCharacter;

public:
	
	UFUNCTION(BlueprintCallable)
	UEnemyWaveManagementSystem* GetWaveManager();

	UFUNCTION(BlueprintCallable)
	UAIAttackSystemComponent* GetAttackSystemComponent();
	
	// Calls WaveManager's SpawnWave function.
	UFUNCTION(BlueprintCallable)
	void SpawnWave();
	
	// Called when a run ends. Moves the player to the scoring/accolades screen. 
	UFUNCTION()
	void EndRun(bool bHasWon);

private:

	FTimerHandle FirstWaveStartTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Wave Management")
	float TimeBeforeFirstWave;
	
	// AIAttackSystemComp to handle level's enemies
	// IMPORTANT - MUST BE ADDED TO GAME MODE'S BLUEPRINT
	UPROPERTY()
	UAIAttackSystemComponent* AIAttackSystemComp;

	/**
	 * @brief Changes the level to the end screen level.
	 * @note called after a delay in UEnemyWaveManagement::EndRun().
	 */
	UFUNCTION()
	void ChangeToEndScreen();

	FTimerHandle RunEndTransferTimerHandle;
	float TimeBeforeChangeToEndScreen = 3.0f;
	
};
