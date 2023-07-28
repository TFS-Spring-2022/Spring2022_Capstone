// Created by Spring2022_Capstone team


#include "EnemyWaveManagementSystem.h"

#include "Kismet/GameplayStatics.h"

void UEnemyWaveManagementSystem::BeginPlay()
{
	Super::BeginPlay();

	CurrentWave = 0;
	
}

void UEnemyWaveManagementSystem::SetEnemySpawnLocations()
{
	// ToDo: Add EnemySpawnPoints to array from EnemySpawnPoint::BeginPlay() (beware execution order).
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnPoint::StaticClass(), EnemySpawnLocations);
}

void UEnemyWaveManagementSystem::SpawnWave()
{
	for (TSubclassOf<ABaseEnemy> EnemyToSpawn : Waves[CurrentWave].EnemiesToSpawn)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		int RandomSpawnSelection = FMath::RandRange(0, EnemySpawnLocations.Num()-1);

		// ToDo: Temporary before spawning finalization.
		// Don't spawn at same point twice to avoid enemy overlap.
		do
		{
			RandomSpawnSelection = FMath::RandRange(0, EnemySpawnLocations.Num()-1);
		}
		while (RandomSpawnSelection == LastSpawnLocationElement);
		
		FVector Location = EnemySpawnLocations[RandomSpawnSelection]->GetActorLocation();
		FRotator Rotation = EnemySpawnLocations[RandomSpawnSelection]->GetActorRotation();
		
		AActor* SpawnedEnemy = GetWorld()->SpawnActor(EnemyToSpawn, &Location, &Rotation, SpawnParams);
		ActiveEnemies.Add(SpawnedEnemy);
	}
	
	CurrentWave++;
	if(CurrentWave > Waves.Num()-1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "UEnemyWaveManagementSystem: Last Wave Complete - End Game");
		// Note - For now I am just going to reset the wave counter.
		CurrentWave = 0;
	}
}
