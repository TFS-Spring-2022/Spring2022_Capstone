// Created by Spring2022_Capstone team


#include "EnemyWaveManagementSystem.h"

#include "Kismet/GameplayStatics.h"

void UEnemyWaveManagementSystem::SetEnemySpawnLocations()
{
	// ToDo: Add EnemySpawnPoints to array from EnemySpawnPoint::BeginPlay() (beware execution order).
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnPoint::StaticClass(), EnemySpawnLocations);
}
