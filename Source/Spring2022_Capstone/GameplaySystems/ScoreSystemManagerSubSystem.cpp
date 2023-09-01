// Created by Spring2022_Capstone team


#include "ScoreSystemManagerSubSystem.h"

#include "ScoreSystemTimerSubSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/BasePickup.h"

void UScoreSystemManagerSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ResetScoreSystem();

	// As the score system manager subsystem is loaded, set a reference to it inside the score system timer subsystem.
	if(UScoreSystemTimerSubSystem* UScoreSystemTimerSubSystem = GetWorld()->GetSubsystem<class UScoreSystemTimerSubSystem>())
		UScoreSystemTimerSubSystem->SetScoreManagerSubSystem(this);
	
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
	Hits = 0;
	EnemiesKilled = 0;
	HeadshotHits = 0;
	HitsWhileAirborne = 0;
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

void UScoreSystemManagerSubSystem::IncrementScoreCounter(EScoreCounters ScoreCounter)
{
	switch (ScoreCounter)
	{
	case EScoreCounters::EnemiesKilled:
		EnemiesKilled++;
		break;
	case EScoreCounters::HeadshotHits:
		HeadshotHits++;
		break;
	case EScoreCounters::HitsWhileAirborne:
		HitsWhileAirborne++;
		break;
	case EScoreCounters::EnemiesKilledWithHazards:
		EnemiesKilledWithHazards++;
		break;
	case EScoreCounters::ElitesKilled:
		ElitesKilled++;
		break;
	case EScoreCounters::SnipersDisabled:
		SnipersDisabled++;
		break;
	case EScoreCounters::Hits: 
		Hits++;
		break;
	default: ;
	}
}

void UScoreSystemManagerSubSystem::CheckWaveEndAccolades()
{
	// I Prefer Treasure Accolade ToDo: FIX ENEMY DROPS SPAWNING MULTIPLE COPIES EVERY TIME THEY SPAWN.
	TArray<AActor*> PickupsInScene;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePickup::StaticClass(), PickupsInScene);
	if(PickupsInScene.Num() - 1 >= I_PREFER_TREASURE_PICKUP_AMOUNT)
	{
		IncrementAccoladeCount(EAccolades::IPreferTreasure);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "I PREFER TREASURE");
	}
		
	PickupsInScene.Empty();
}
