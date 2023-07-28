// Copyright Epic Games, Inc. All Rights Reserved.


#include "Spring2022_CapstoneGameModeBase.h"

void ASpring2022_CapstoneGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Create an instance of EnemyWaveManager BP assigned in the details panel. 
	EnemyWaveManagerInstance = NewObject<UEnemyWaveManagementSystem>(this, LevelEnemyWaveManagerBP);
	EnemyWaveManagerInstance->DEBUG_PublicCall(); // Quick test to ensure proper creation.

}
