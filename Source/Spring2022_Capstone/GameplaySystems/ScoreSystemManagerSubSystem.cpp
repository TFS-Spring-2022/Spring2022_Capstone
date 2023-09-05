// Created by Spring2022_Capstone team


#include "ScoreSystemManagerSubSystem.h"

#include "ScoreSystemTimerSubSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/BasePickup.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

void UScoreSystemManagerSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ResetScoreSystem();

}

void UScoreSystemManagerSubSystem::SetPlayerReference(APlayerCharacter* Player)
{
	PlayerCharacter = Player;
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
	Accolade_HotHeadedCount = 0;
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
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "SKULL N CROSSHAIR!");
		break;
	case CaptainOfWar:
		Accolade_CaptainOfWarCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "CAPTAIN OF WAR!");
		break;
	case SkyPirate:
		Accolade_SkyPirateCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "SKY PIRATE!");
		break;
	case LandLubber:
		Accolade_LandLubberCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "LANDLUBBER!");
		break;
	case CloseCallCorsair:
		Accolade_CloseCallCorsairCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "CLOSE CALL CORSAIR!");
		break;
	case Opportunist:
		Accolade_OpportunistCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "OPPORTUNIST!");
		break;
	case CaptainsCoup:
		Accolade_CaptainsCoupCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "CAPTAINS COUP");
		break;
	case DoubleAerialPlunder:
		Accolade_DoubleAerialPlunderCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "DOUBLE AERIAL PLUNDER!");
		break;
	case BlunderBlast:
		Accolade_BlunderBlastCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "BLUNDER BLAST!");
		break;
	case SkyBuccaneer:
		Accolade_SkyBuccaneerCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "SKY BUCCANEER!");
		break;
	case HotHeaded:
		Accolade_HotHeadedCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "HOT HEADED!");
		break;
	case NimbleBones:
		Accolade_NimbleBonesCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "NIMBLE BONES!");
		break;
	case DeathDodger:
		Accolade_DeathDodgerCount++;
		GEngine->AddOnScreenDebugMessage(-1 ,2.f, FColor::Green, "DEATH DODGER!");
		break;
	case PiratesFortitude:
		Accolade_PiratesFortitudeCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "PIRATES FORTITUDE!");
		break;
	case PlunderersProwess:
		Accolade_PlunderersProwessCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "PLUNDERERS PROWESS!");
		break;
	case IPreferTreasure:
		Accolade_IPreferTreasureCount++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "I PREFER TREASURE!");
		break;
	case PirateBlitz:
		Accolade_PirateBlitz++;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "PIRATE BLITZ!");
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
	// I Prefer Treasure Accolade
	TArray<AActor*> PickupsInScene;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePickup::StaticClass(), PickupsInScene);
	if(PickupsInScene.Num() - 1 >= I_PREFER_TREASURE_PICKUP_AMOUNT)
		IncrementAccoladeCount(EAccolades::IPreferTreasure);
	PickupsInScene.Empty();

	// Death Dodger Accolade
	if(DeathDodgerCount >= DEATH_DODGER_AMOUNT)
		IncrementAccoladeCount(EAccolades::DeathDodger);
	DeathDodgerCount = 0;
}

void UScoreSystemManagerSubSystem::IncrementDeathDodgerCount()
{
	DeathDodgerCount++;
}

float UScoreSystemManagerSubSystem::GetCounterValue(EScoreCounters Counter)
{
	switch (Counter)
	{
	case EScoreCounters::Hits: 
		return Hits;
	case EScoreCounters::EnemiesKilled:
		return EnemiesKilled;
	case EScoreCounters::HeadshotHits:
		return HeadshotHits;
	case EScoreCounters::HitsWhileAirborne:
		return HitsWhileAirborne;
	case EScoreCounters::EnemiesKilledWithHazards:
		return EnemiesKilledWithHazards;
	case EScoreCounters::ElitesKilled:
		return ElitesKilled;
	case EScoreCounters::SnipersDisabled:
		return SnipersDisabled;
	default: return 9999;
	}
}

int UScoreSystemManagerSubSystem::GetAccoladeCount(EAccolades Accolade)
{
	switch (Accolade)
	{
	case SkullNCrosshair: 
		return Accolade_SkullNCrosshairCount;
	case CaptainOfWar: 
		return Accolade_CaptainOfWarCount;
	case SkyPirate:
		return Accolade_SkyPirateCount;
	case LandLubber: 
		return Accolade_LandLubberCount;
	case CloseCallCorsair:
		return Accolade_CloseCallCorsairCount;
	case Opportunist:
		return Accolade_OpportunistCount;
	case CaptainsCoup:
		return Accolade_CaptainsCoupCount;
	case DoubleAerialPlunder:
		return Accolade_DoubleAerialPlunderCount;
	case BlunderBlast:
		return Accolade_BlunderBlastCount;
	case SkyBuccaneer:
		return Accolade_SkyBuccaneerCount;
	case HotHeaded:
		return Accolade_HotHeadedCount;
	case NimbleBones:
		return Accolade_NimbleBonesCount;
	case DeathDodger:
		return Accolade_DeathDodgerCount;
	case PiratesFortitude:
		return Accolade_PiratesFortitudeCount;
	case PlunderersProwess:
		return Accolade_PlunderersProwessCount;
	case IPreferTreasure:
		return Accolade_IPreferTreasureCount;
	case PirateBlitz:
		return Accolade_PirateBlitz;
	default: GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Could not find accolade count");
		return 9999;
	}
}

void UScoreSystemManagerSubSystem::CheckHotHeaded()
{
		if(PlayerCharacter->GetWeapon1()->GetIsOverheating() && PlayerCharacter->GetWeapon2()->GetIsOverheating())
			IncrementAccoladeCount(EAccolades::HotHeaded);
}
