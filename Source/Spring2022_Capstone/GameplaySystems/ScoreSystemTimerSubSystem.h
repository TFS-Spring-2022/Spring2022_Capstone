// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "ScoreSystemManagerSubSystem.h"
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

	// Required to run
	virtual TStatId GetStatId() const override
	{
		return GetStatID();
	}

	// Reference to the ScoreSystemManagerSubSystem, set from UScoreSystemManagerSubSystem::Initialize().
	UPROPERTY()
	UScoreSystemManagerSubSystem* ScoreManagerSubSystem;

public:

	void SetScoreManagerSubSystem(UScoreSystemManagerSubSystem* SubSystem);

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
	/**
	 * @brief Called from EnemyWaveManagementSystem at the end of a wave. Checks if the player has beat the
	 * wave before PIRATE_BLITZ_TIME_REQUIREMENT.
	 */
	void FinishWave();

	bool bCaptainsCoupTimerStarted = false;
	float CaptainsCoupTimer = 0.0f;

	bool bSkullNCrosshairTimerStarted = false;
	float SkullNCrosshairTimer = 0.0f;
	int SkullNCrosshairHeadshotHits = 0;
	void IncrementScullNCrosshairHeadshotHits();

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
	const int SKULL_N_CROSSHAIR_HEADSHOT_REQUIREMENT = 3.0f;	// Player must hit this many headshots before SKULL_N_CROSSHAIR_TIME_REQUIREMENT has elapsed.  
	
};
