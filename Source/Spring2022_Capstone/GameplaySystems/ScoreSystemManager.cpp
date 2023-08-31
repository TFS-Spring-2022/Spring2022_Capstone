// Created by Spring2022_Capstone team


#include "ScoreSystemManager.h"

void UScoreSystemManager::ResetScoreSystem()
{
	// Accolades:
	TotalAccoladesCount = 0;
	Accolade_BrainSurgeonCount = 0;
	Accolade_LordOfWarCount = 0;
	Accolade_SkyPirateCount = 0;
	Accolade_LandLubberCount = 0;
	Accolade_BulletSpongeCount = 0;
	Accolade_OpportunistCount = 0;
	Accolade_GiantSlayerCount = 0;
	Accolade_LastShadowCount = 0;
	Accolade_BlunderBlastCount = 0;
	Accolade_ThunderClapCount = 0;
	Accolade_CoolHeadedCount = 0;
	Accolade_NimbleBonesCount = 0;
	Accolade_DeathDodgerCount = 0;
	Accolade_NoSweatCount = 0;
	Accolade_2EZCount = 0;
	Accolade_IPreferTreasureCount = 0;
	Accolade_BulletStormCount = 0;
	
	// Score:
	TotalScore = 0.0f;
	EnemiesKilled = 0;
	EnemiesKilledWithHeadshot = 0;
	EnemiesKilledWhileAirborne = 0;
	EnemiesKilledWithHazards = 0;
	ElitesKilled = 0;
	SnipersDisabled = 0;
	RunCompletionTime = 0.0f;

	// Assorted Fun Stats:
	FastestWaveTime = 0.0f;
	SlowestWaveTime = 0.0f;
	TotalDistanceTravelled = 0.0f;
	MostDistanceTravelledInAWave = 0.0f;
	LeastDistanceTravelledInAWave = 0.0f;
	TotalTimeSpentAirborne = 0.0f;
	TotalTimeSpentGrounded = 0.0f;
	MostShotsFiredInAWave = 0;
	LeastShotsFiredInAWave = 0;
}
