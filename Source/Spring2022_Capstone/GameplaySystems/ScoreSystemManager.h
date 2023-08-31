// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScoreSystemManager.generated.h"

/**
 * A class used to handle the score and accolades earned by a player through a run.
 */
UCLASS()
class SPRING2022_CAPSTONE_API UScoreSystemManager : public UObject
{
	GENERATED_BODY()
	
	// Accolades:
	int TotalAccoladesCount = 0;
	
	// Brain Surgeon: 3 Headshots in 5 seconds.
	int Accolade_BrainSurgeonCount = 0;

	// Lord of War: 5 Kills in 5 seconds.
	int Accolade_LordOfWarCount = 0;
	
	// Sky Pirate: 15 seconds since last touched the ground.
	int Accolade_SkyPirateCount = 0;
	
	// Land Lubber: 30 seconds spent consecutively on the ground.
	int Accolade_LandLubberCount = 0;
	
	// Bullet Sponge: Love over 60% max health in 3 seconds.
	int Accolade_BulletSpongeCount = 0;
	
	// Opportunist: 4 enemies damaged by a single exploding hazard.
	int Accolade_OpportunistCount = 0;

	// Giant Slayer: Elite killed in under 6 seconds (after first hit).
	int Accolade_GiantSlayerCount = 0;
	
	// Last Shadow: 2 enemies killed while airborne.
	int Accolade_LastShadowCount = 0;
	
	// Blunder Blast: More then 1 enemy killed with a shotgun blast on the ground.
	int Accolade_BlunderBlastCount = 0;
	
	// Thunder Clap: More then 1 enemy killed with a shotgun blast while airborne.
	int Accolade_ThunderClapCount = 0;
	
	// Cool Headed: 1 minute spent between overheats.
	int Accolade_CoolHeadedCount = 0;
	
	// Nimble Bones: 3 Sniper Shots avoided (zero damage).
	int Accolade_NimbleBonesCount = 0;
	
	// Death Dodger: Recovered from less then 20% health 2 times in one wave.
	int Accolade_DeathDodgerCount = 0;
	
	// No Sweat: Spent more then half the wave duration at over 50% health.
	int Accolade_NoSweatCount = 0;
	
	// 2EZ: Spent more then half the wave duration at over 80% health.
	int Accolade_2EZCount = 0;
	
	// I Prefer Treasure: More then 4 pickups not collected at the end of a wave.
	int Accolade_IPreferTreasureCount = 0;
	
	// Bullet Storm: Wave completed in less then 2 minutes.
	int Accolade_BulletStormCount = 0;
	
	// Score:
	float TotalScore = 0.0f;
	
	// Enemies killed.
	int EnemiesKilled = 0;
	
	// Enemies killed by headshot.
	int EnemiesKilledWithHeadshot = 0; 

	// Enemies killed while airborne.
	int EnemiesKilledWhileAirborne = 0;
	
	// Enemies killed with hazards.
	int EnemiesKilledWithHazards = 0;
	
	// Number of elites killed.
	int ElitesKilled = 0;
	
	// Number of snipers/towers disabled.
	int SnipersDisabled = 0;
	
	// Run completion time.
	float RunCompletionTime = 0.0f;

	// Assorted Fun Stats:
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
	
};
