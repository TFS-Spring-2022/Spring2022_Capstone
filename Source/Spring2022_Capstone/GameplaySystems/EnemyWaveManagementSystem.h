// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "EnemySpawnPoint.h"
#include "Spring2022_Capstone/Enemies/BaseEnemy.h"
#include "Spring2022_Capstone/Enemies/Sniper/SniperEnemy.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "Spring2022_Capstone/UI/HUD/WaveAnnouncerWidget.h"
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

	UPROPERTY()
	USoundManagerSubSystem* SoundManagerSubSystem;

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

	UPROPERTY()
	int CurrentWave;

	// Enemies in the current wave
	UPROPERTY(VisibleAnywhere, Category = "Waves")
	TArray<AActor*> ActiveEnemies;
	
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;

	// Time in S before spawn wave is called after finishing a round.
	UPROPERTY(EditAnywhere, Category = "Waves")
	float TimeBeforeNextRoundStart = 0.1;

	UPROPERTY(EditAnywhere, Category = "Waves")
	float TimeBeforeOpeningUpgradeMenu = 2.5;

	FTimerHandle TimeBeforeNextRoundStartTimerHandle;
	FTimerHandle TimeBeforeUpgradeMenuTimerHandle; // Unsure on this usage
	FTimerHandle OpenUpgradeMenuTimerHandle; // Used to handle opening the upgrade menu after a delay.
	FTimerHandle TimeBeforeWaveStartVoiceLine;
	FTimerHandle TimeBeforeClearDeadEnemiesTimerHandle;
	FTimerHandle TimeStopSoundDelay;

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

	// Wave Announcer Widget to be created
	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<UWaveAnnouncerWidget> WaveAnnouncerWidgetBP;

	// Announcer Widget Instance
	UPROPERTY()
	UWaveAnnouncerWidget* WaveAnnouncerWidgetInstance;
	
public:

	// ToDo: Find a more effective way to handle this. I tried to add in EnemySpawnPoint::BeginPlay() but execution order causes it to null reference.
	// Grabs all EnemySpawnPoint actors in scene and adds them to EnemySpawnLocations.
	void SetEnemySpawnLocations();

	UFUNCTION()
	void SpawnWave();

	UFUNCTION()
	void SpawnEnemy(TSubclassOf<ABaseEnemy> SpawningEnemy);

	// Has an elite enemy been spawned this round?
	UPROPERTY()
	bool bEliteEnemySpawnedThisWave = false;

	// The last element of EnemySpawnLocations an enemy was created at.
	UPROPERTY()
	int LastSpawnLocationElement;
	
	const float MINIMUM_TIME_BETWEEN_SPAWNS = 3.0f; // Minimum time between each enemy spawn.
	const float SPAWN_DELAY_MINIMUM_BUFFER = 3.0f;	// Bottom of the random range added to MINIMUM_TIME_BETWEEN_SPAWNS for SpawnDelay calculation.
	const float SPAWN_DELAY_MAXIMUM_BUFFER = 7.5f;	// Top of the random range added to MINIMUM_TIME_BETWEEN_SPAWNS for SpawnDelay calculation.

	UPROPERTY()
	int EnemiesKilledThisWave = 0;

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

	//Sound 
	void PlayWaveStartVoiceLine() const;
	void FadeOutMusic();
	
	// Called every Tick
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetElapsedWaveTime() const;
	
	FORCEINLINE UWaveAnnouncerWidget* GetWaveAnnouncerWidget() const {return WaveAnnouncerWidgetInstance;}
};
