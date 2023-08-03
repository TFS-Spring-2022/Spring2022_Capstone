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

public:
	
	UFUNCTION(BlueprintCallable)
	UEnemyWaveManagementSystem* GetWaveManager();

	// Calls WaveManager's SpawnWave function.
	UFUNCTION(BlueprintCallable)
	void SpawnWave();

private:

	FTimerHandle FirstWaveStartTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Wave Management")
	float TimeBeforeFirstWave;
public:

	//Variables are contained in Gamemode as it is persistent in the scene regardless of whether a player dies or not.
	//Can be added to player controller as well

	UPROPERTY(BlueprintReadWrite, Category = "Player Score")
		int PlayerKills;

	UPROPERTY(EditDefaultsOnly, Category = "Player Score")
		int MaxPlayerKills;

	UFUNCTION(BlueprintCallable)
		void IncrementKills();
	
};
