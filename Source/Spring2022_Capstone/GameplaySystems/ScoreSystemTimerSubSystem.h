// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "ScoreSystemManagerSubSystem.h"
#include "Spring2022_Capstone/Sounds/SoundManagerSubSystem.h"
#include "Subsystems/WorldSubsystem.h"
#include "ScoreSystemTimerSubSystem.generated.h"
// ToDo: Make not a SubSystem (see ResetScoreSystemTimerSubSystem() comment).
/**
 * A TickableWorldSubsystem used to communicate with the ScoreSystemManagerSubsystem and handle awarding
 * time based accolades.
 */
UCLASS()
class SPRING2022_CAPSTONE_API UScoreSystemTimerSubSystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	// Required to run
	virtual TStatId GetStatId() const override
	{
		return GetStatID();
	}

	// Reference to the ScoreSystemManagerSubSystem, set from UScoreSystemManagerSubSystem::Initialize().
	UPROPERTY()
	UScoreSystemManagerSubSystem* ScoreManagerSubSystem;

	UPROPERTY()
	class UEnemyWaveManagementSystem* WaveManager;

public:

	void SetScoreManagerSubSystem(UScoreSystemManagerSubSystem* SubSystem);

	/**
	 * @brief Set's the ScoreSystemTimerSubSystem's reference to the player's character.
	 * @note Called from APlayerCharacter::BeginPlay() due to execution order.
	 * @param Player 
	 */
	void SetPlayerReference(class APlayerCharacter* Player);

	/**
	 * @brief 
	 * @note Called from EnemyWaveManagementSystem::SpawnWave() due to execution order.
	 * @param WaveManagerInstance 
	 */
	void SetWaveManagerReference(class UEnemyWaveManagementSystem* WaveManagerInstance);

	// Starts the timer for the given accolade.
	void StartAccoladeTimer(EAccolades Accolade);
	// Stops and clears the timer for the given accolade.
	void StopAccoladeTimer(EAccolades Accolade);
	// Returns the status of the accolade timer.
	bool IsAccoladeTimerRunning(EAccolades Accolade);

	bool bSkyPirateTimerStarted = false;
	float SkyPirateTimer = 0.0f;

	bool bLandLubberTimerStarted = false;
	float LandLubberTimer = 0.0f;

	bool bPirateBlitzTimerStarted = false;
	float PirateBlitzTimer = 0.0f;


	//Sounds
	UPROPERTY()
	USoundManagerSubSystem* SoundManagerSubSystem;
	
	/**
	 * @brief Called from EnemyWaveManagementSystem at the end of a wave. Checks accolades that
	 * reference round time.
	 */
	void FinishWave();

	bool bCaptainsCoupTimerStarted = false;
	float CaptainsCoupTimer = 0.0f;

	bool bSkullNCrosshairTimerStarted = false;
	float SkullNCrosshairTimer = 0.0f;
	int SkullNCrosshairHeadshotHits = 0;
	void IncrementScullNCrosshairHeadshotHits();

	bool bCloseCallCorsairTimerStarted = false;
	float CloseCallCorsairTimer = 0.0f;
	float CloseCallCorsairHealthTarget = 0.0f;
	float CloseCallCorsairHealthEntryPoint = 0.0f;

	bool bCaptainOfWarTimerStarted = false;
	float CaptainOfWarTimer = 0.0f;
	int CaptainOfWarKills = 0;
	void IncrementCaptainOfWarKills();

	void StartWave();
	bool bWaveStarted = false;
	float PiratesFortitudeTimeInRange = 0.0f;
	float PlunderersProwessTimeInRange = 0.0f;

private:

	// ToDo: Remove after changing parent.
	// Resets timer values. Called every time the ScoreSystemTimer is loaded. It is not necessary to
	// maintain information as it is passed to the ScoreSystemManagerSubSystem.
	void ResetScoreSystemTimerSubSystem();

	// Accolade Time Requirements:
	const float SKY_PIRATE_TIME_REQUIREMENT = 5.0f;				// Player must stay in the air for this amount of time(s). ToDo: 10/15 in actuality just 5.0f for testing/showing.
	const float LAND_LUBBER_TIME_REQUIREMENT = 15.0f;			// Player must remain on the ground for this amount of time(s).
	const float PIRATE_BLITZ_TIME_REQUIREMENT = 100.0f;			// Player must clear the wave before this time(s) elapses.
	const float CAPTAINS_COUP_TIME_REQUIREMENT = 6.0f;			// Player must kill an enemy elite in under this time(s) after their first hit.
	const float SKULL_N_CROSSHAIR_TIME_REQUIREMENT = 5.0f;		// Player must hit SKULL_N_CROSSHAIR_HEADSHOT_REQUIREMENT headshots before this time elapses.
	const int SKULL_N_CROSSHAIR_HEADSHOT_REQUIREMENT = 3;		// Player must hit this many headshots before SKULL_N_CROSSHAIR_TIME_REQUIREMENT has elapsed.  
	const float CLOSE_CALL_CORSAIR_HEALTH_PERCENTAGE = 60.0f;	// Percentage of max health the player must lose before CLOSE_CALL_CORSAIR_TIME_REQUIREMENT has elapsed.
	const float CLOSE_CALL_CORSAIR_TIME_REQUIREMENT = 3.0f;		// Player must lose CLOSE_CALL_CORSAIR_HEALTH_PERCENTAGE of their max health before this time(s) has elapsed.
	const int CAPTAIN_OF_WAR_KILL_REQUIREMENT = 3;				// Player must kill this many enemies before CAPTAIN_OF_WAR_TIME_REQUIREMENT has elapsed. ToDo: 2.0 is a test value regular should be 5
	const float CAPTAIN_OF_WAR_TIME_REQUIREMENT = 5.0f;			// Player must kill CAPTAIN_OF_WAR_KILL_REQUIREMENT enemies before this time has elapsed.
	const float PIRATES_FORTITUDE_HEALTH_PERCENTAGE = 50.0f;	// Player must keep their health above this percentage for more then half the wave duration.
	const float PLUNDERERS_PROWESS_HEALTH_PERCENTAGE = 80.0f;	// Player must keep their health above this percentage for more then half the wave duration.
	
};
