// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplaySystems/EnemyWaveManagementSystem.h"
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
	UPROPERTY()
	UEnemyWaveManagementSystem* EnemyWaveManagerInstance;
	
};
