// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "EnemySpawnPoint.h"
#include "Spring2022_Capstone/Enemies/BaseEnemy.h"
#include "Spring2022_Capstone/Enemies/Sniper/SniperEnemy.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
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

	UEnemyWaveManagementSystem();

	virtual void BeginPlay() override;
	
	// Set of enemies to be spawned at the start of a new wave.
	UPROPERTY(EditAnywhere, Category = "Waves")
	TArray<FEnemyWave> Waves;

	// All available spawn points in current level
	UPROPERTY(EditAnywhere, Category = "Waves")
	TArray<AActor*> EnemySpawnLocations;

	// All Snipers in the current level
	UPROPERTY(VisibleAnywhere, Category = "Waves")
	TArray<AActor*> SniperEnemies;

	// The last element of EnemySpawnLocations an enemy was created at.
	int LastSpawnLocationElement;

	int CurrentWave;

	// Enemies in the current wave
	UPROPERTY(VisibleAnywhere, Category = "Waves")
	TArray<AActor*> ActiveEnemies;
	
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;

	// Time in S before spawn wave is called after finishing a round.
	UPROPERTY(EditAnywhere, Category = "Waves")
	float TimeBeforeNextRoundStart = 0.1;

	FTimerHandle TimeBeforeNextRoundStartTimerHandle;
	FTimerHandle TimeBeforeUpgradeMenuTimerHandle;
	FTimerHandle TimeBeforeClearDeadEnemiesTimerHandle;

	// Used to open the player's upgrade menu through a timer.
	UFUNCTION()
	void OpenUpgradeMenu() const;

	UPROPERTY()
	UScoreSystemTimerSubSystem* ScoreSystemTimerSubSystem;

	UPROPERTY()
	UScoreSystemManagerSubSystem* ScoreSystemManagerSubSystem;

	UPROPERTY(VisibleAnywhere)
	float ElapsedWaveTime = 0.0f; // Total seconds the round has been active for.

	// Converts the round timer from seconds to minutes:seconds and prints to screen.
	void ConvertWaveTime(float DTime);
	float WaveTimerSeconds = 0.0f; // Used for converting total seconds to minutes:seconds
	int WaveTimerMinutes = 0.0f;	// Used for converting total seconds to minutes:seconds
	
public:

	// ToDo: Find a more effective way to handle this. I tried to add in EnemySpawnPoint::BeginPlay() but execution order causes it to null reference.
	// Grabs all EnemySpawnPoint actors in scene and adds them to EnemySpawnLocations.
	void SetEnemySpawnLocations();

	UFUNCTION()
	void SpawnWave();

	// Remove an ActiveEnemy from ActiveEnemies array.
	void RemoveActiveEnemy(AActor* EnemyToRemove);

	// All enemy corpses to be destroyed at the next rounds start.
	UPROPERTY(VisibleAnywhere, Category = "Waves")
	TArray<AActor*> EnemiesToDestroy;

	// Destroys all enemy corpses in current wave
	UFUNCTION()
	void ClearDeadEnemies();

	// Used to call checks for accolades and start the next round after a delay.
	void StartNextRound();

	// Called every Tick
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetElapsedWaveTime() const;
	
};
