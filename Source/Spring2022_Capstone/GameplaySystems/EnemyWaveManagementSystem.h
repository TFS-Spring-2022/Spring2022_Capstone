// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
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

private:

	// Set of enemies to be spawned at the start of a new wave.
	UPROPERTY(EditAnywhere, Category = "Waves")
	TArray<FEnemyWave> Waves;

public:
	
	UPROPERTY(EditAnywhere, Category = "DEBUG")
	float DEBUG_FloatValue;
	
	// Using to test, just prints to UE_Log the value of DEBUG_FloatValue.
	void DEBUG_PublicCall();

};
