// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScoreSystemManagerSubSystem.generated.h"

// All the accolades the player can earn during gameplay.
UENUM()
enum EAccolades
{
	SkullNCrosshair,		// SkullNCrosshair: 3 Headshots in 5 seconds.
	CaptainOfWar,			// CaptainOfWar: 5 Kills in 5 seconds.
	SkyPirate,				// Sky Pirate: 15 seconds since last touched the ground.
	LandLubber,				// Land Lubber: 30 seconds spent consecutively on the ground.
	CloseCallCorsair,		// CloseCallCorsair: Lose over 60% max health in 3 seconds.
	Opportunist,			// Opportunist: 4 enemies damaged by a single exploding hazard.
	CaptainsCoup,			// CaptainsCoup: Elite killed in under 6 seconds (after first hit).
	DoubleAerialPlunder,	// DoubleAerialPlunder: 2 enemies killed while airborne.
	BlunderBlast,			// Blunder Blast: More then 1 enemy killed with a shotgun blast on the ground.
	SkyBuccaneer,			// Sky Buccaneer: More then 1 enemy killed with a shotgun blast while airborne.
	CoolHeaded,				// Cool Headed: 1 minute spent between overheats.
	NimbleBones,			// Nimble Bones: 3 Sniper Shots avoided (zero damage).
	DeathDodger,			// Death Dodger: Recovered from less then 20% health 2 times in one wave.
	PiratesFortitude,		// PiratesFortitude: Spent more then half the wave duration at over 50% health.
	PlunderersProwess,		// PlunderersProwess: Spent more then half the wave duration at over 80% health.
	IPreferTreasure,		// I Prefer Treasure: More then 4 pickups not collected at the end of a wave.
	PirateBlitz,			// PirateBlitz: Wave completed in less then 2 minutes.
};

UENUM()
enum EScoreCounters
{
	Hits,
	EnemiesKilled,
	HeadshotHits,
	HitsWhileAirborne,
	EnemiesKilledWithHazards,
	ElitesKilled,
	SnipersDisabled,
};

/**
 * A class used to handle the score and accolades earned by a player through a run.
 */
UCLASS()
class SPRING2022_CAPSTONE_API UScoreSystemManagerSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	// Called when subsystem is first loaded.
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Accolades:
	int TotalAccoladesCount = 0;
	int Accolade_SkullNCrosshairCount = 0;
	int Accolade_CaptainOfWarCount = 0;
	int Accolade_SkyPirateCount = 0;
	int Accolade_LandLubberCount = 0;
	int Accolade_CloseCallCorsairCount = 0;
	int Accolade_OpportunistCount = 0;
	int Accolade_CaptainsCoupCount = 0;
	int Accolade_DoubleAerialPlunderCount = 0;
	int Accolade_BlunderBlastCount = 0;
	int Accolade_SkyBuccaneerCount = 0;
	int Accolade_CoolHeadedCount = 0;
	int Accolade_NimbleBonesCount = 0;
	int Accolade_DeathDodgerCount = 0;
	int Accolade_PiratesFortitudeCount = 0;
	int Accolade_PlunderersProwessCount = 0;
	int Accolade_IPreferTreasureCount = 0;
	int Accolade_PirateBlitz = 0;
	
	// Score:
	float TotalScore = 0.0f;

	// Counters
	int Hits;
	int EnemiesKilled = 0;
	int HeadshotHits = 0; 
	int HitsWhileAirborne = 0;
	int EnemiesKilledWithHazards = 0; // ToDo: Implement when hazards are merged.
	int ElitesKilled = 0;
	int SnipersDisabled = 0; // ToDo: Implement when Sniper Disabled in merged.
	
	// Run completion time.
	float RunCompletionTime = 0.0f;

	// ToDo: Assorted Fun Stats:
	// Fastest wave.
	float FastestWaveTime = 0.0f;
	// Slowest wave.
	float SlowestWaveTime = 0.0f;
	// Total distance travelled.
	float TotalDistanceTravelled = 0.0f;
	// Most distance travelled in a wave.
	float MostDistanceTravelledInAWave = 0.0f;
	// Least distance travelled in a wave
	float LeastDistanceTravelledInAWave = 0.0f;
	// Total time spent airborne.
	float TotalTimeSpentAirborne = 0.0f;
	// Total time spent on the ground.
	float TotalTimeSpentGrounded = 0.0f;
	// Most shots fired in a wave.
	int MostShotsFiredInAWave = 0;
	// Least shots fired in a wave.
	int LeastShotsFiredInAWave = 0;

public:

	// Clears all accolades, scores, and stats.
	void ResetScoreSystem();

	// Increments the counter for the given accolade.
	UFUNCTION()
	void IncrementAccoladeCount(EAccolades Accolade);

	// Increments the counter for the given score counter.
	UFUNCTION()
	void IncrementScoreCounter(EScoreCounters ScoreCounter);

	// Called at the end of a wave to check the status of wave based accolades.
	void CheckWaveEndAccolades();

	int DeathDodgerCount = 0;
	void IncrementDeathDodgerCount();

private:

	const int I_PREFER_TREASURE_PICKUP_AMOUNT =	4;		// Number of pickups that must remain on the scene at wave end for accolade.
	const float DEATH_DODGER_HEALTH_PERCENTAGE = 20.0f;	// Player must recover from this health amount DEATH_DODGER_AMOUNT times in a wave.
	const int DEATH_DODGER_AMOUNT = 2;					// Player must recover DEATH_DODGER_HEALTH_PERCENTAGE this many times in a wave.

public:

	FORCEINLINE float GetDeathDodgerHealthPercentage() const {return DEATH_DODGER_HEALTH_PERCENTAGE;}
	
};
