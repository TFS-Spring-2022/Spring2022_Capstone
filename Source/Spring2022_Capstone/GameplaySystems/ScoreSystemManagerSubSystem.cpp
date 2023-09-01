// Created by Spring2022_Capstone team


#include "ScoreSystemManagerSubSystem.h"

void UScoreSystemManagerSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ResetScoreSystem();
}

void UScoreSystemManagerSubSystem::ResetScoreSystem()
{
	// Accolades:
	TotalAccoladesCount = 0;
	Accolade_SkullNCrosshairCount = 0;
	Accolade_CaptainOfWarCount = 0;
	Accolade_SkyPirateCount = 0;
	Accolade_LandLubberCount = 0;
	Accolade_CloseCallCorsairCount = 0;
	Accolade_OpportunistCount = 0;
	Accolade_CaptainsCoupCount = 0;
	Accolade_DoubleAerialPlunderCount = 0;
	Accolade_BlunderBlastCount = 0;
	Accolade_SkyBuccaneerCount = 0;
	Accolade_CoolHeadedCount = 0;
	Accolade_NimbleBonesCount = 0;
	Accolade_DeathDodgerCount = 0;
	Accolade_PiratesFortitudeCount = 0;
	Accolade_PlunderersProwessCount = 0;
	Accolade_IPreferTreasureCount = 0;
	Accolade_PirateBlitz = 0;
	
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

void UScoreSystemManagerSubSystem::IncrementAccoladeCount(const EAccolades Accolade)
{
	switch (Accolade)
	{
	case SkullNCrosshair:
		Accolade_SkullNCrosshairCount++;
		break;
	case CaptainOfWar:
		Accolade_CaptainOfWarCount++;
		break;
	case SkyPirate:
		Accolade_SkyPirateCount++;
		break;
	case LandLubber:
		Accolade_LandLubberCount++;
		break;
	case CloseCallCorsair:
		Accolade_CloseCallCorsairCount++;
		break;
	case Opportunist:
		Accolade_OpportunistCount++;
		break;
	case CaptainsCoup:
		Accolade_CaptainsCoupCount++;
		break;
	case DoubleAerialPlunder:
		Accolade_DoubleAerialPlunderCount++;
		break;
	case BlunderBlast:
		Accolade_BlunderBlastCount++;
		break;
	case SkyBuccaneer:
		Accolade_SkyBuccaneerCount++;
		break;
	case CoolHeaded:
		Accolade_CoolHeadedCount++;
		break;
	case NimbleBones:
		Accolade_NimbleBonesCount++;
		break;
	case DeathDodger:
		Accolade_DeathDodgerCount++;
		break;
	case PiratesFortitude:
		Accolade_PiratesFortitudeCount++;
		break;
	case PlunderersProwess:
		Accolade_PlunderersProwessCount++;
		break;
	case IPreferTreasure:
		Accolade_IPreferTreasureCount++;
		break;
	case PirateBlitz:
		Accolade_PirateBlitz++;
		break;
	default:;
	}

	TotalAccoladesCount++;
}

int UScoreSystemManagerSubSystem::GetTestCount()
{
	return Accolade_SkullNCrosshairCount;
}
