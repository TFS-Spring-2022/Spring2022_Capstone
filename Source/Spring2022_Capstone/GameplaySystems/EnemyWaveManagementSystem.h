// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "EnemySpawnPoint.h"
#include "Spring2022_Capstone/Enemies/BaseEnemy.h"
#include "EnemyWaveManagementSystem.generated.h"

USTRUCT()
struct FEnemyWave
{
	GENERATED_BODY()

	// Blueprints of enemies to be spawned.
	UPROPERTY(EditAnywhere, Category = "Enemies")
	TArray<TSubclassOf<ABaseEnemy>> EnemiesToSpawn;
	
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class SPRING2022_CAPSTONE_API UEnemyWaveManagementSystem : public UActorComponent 
{
	GENERATED_BODY()
	
	// Set of enemies to be spawned at the start of a new wave.
	UPROPERTY(EditAnywhere, Category = "Waves")
	TArray<FEnemyWave> Waves;

	// All available spawn points in current level
	UPROPERTY(EditAnywhere, Category = "Waves")
	TArray<AActor*> EnemySpawnLocations;
	
public:

	// ToDo: Find a more effective way to handle this. I tried to add in EnemySpawnPoint::BeginPlay() but execution order causes it to null reference.
	// Grabs all EnemySpawnPoint actors in scene and adds them to EnemySpawnLocations.
	void SetEnemySpawnLocations();

};
