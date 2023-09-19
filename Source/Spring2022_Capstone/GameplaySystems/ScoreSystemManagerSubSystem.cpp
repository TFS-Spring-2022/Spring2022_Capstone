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
	if(!SoundManagerSubSystem)
		SoundManagerSubSystem = GetGameInstance()->GetSubsystem<USoundManagerSubSystem>();

	switch (Accolade)
	{
	case SkullNCrosshair:
		Accolade_SkullNCrosshairCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("SKULL N' CROSSHAIR!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "SKULL N CROSSHAIR!");
		break;
	case CaptainOfWar:
		Accolade_CaptainOfWarCount++;
		if(SoundManagerSubSystem)
			SoundManagerSubSystem->PlayPlayerSoundEvent(PlayerCharacter->PlayerVoiceAudioComp, 13);
		PlayerCharacter->AnnounceAccolade(FText::FromString("CAPTAIN OF WAR!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "CAPTAIN OF WAR!");
		break;
	case SkyPirate:
		Accolade_SkyPirateCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("SKY PIRATE!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "SKY PIRATE!");
		break;
	case LandLubber:
		Accolade_LandLubberCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("LANDLUBBER!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "LANDLUBBER!" );
		break;
	case CloseCallCorsair:
		Accolade_CloseCallCorsairCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("CLOSE CALL CORSAIR!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "CLOSE CALL CORSAIR!");
		break;
	case Opportunist:
		Accolade_OpportunistCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("OPPORTUNIST!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "OPPORTUNIST!");
		break;
	case CaptainsCoup:
		Accolade_CaptainsCoupCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("CAPTAINS COUP!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "CAPTAINS COUP");
		break;
	case DoubleAerialPlunder:
		Accolade_DoubleAerialPlunderCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("DOUBLE AERIAL PLUNDER!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "DOUBLE AERIAL PLUNDER!");
		break;
	case BlunderBlast:
		Accolade_BlunderBlastCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("BLUNDER BLAST!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "BLUNDER BLAST!");
		break;
	case SkyBuccaneer:
		Accolade_SkyBuccaneerCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("SKY BUCCANEER!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "SKY BUCCANEER!");
		break;
	case HotHeaded:
		Accolade_HotHeadedCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("HOT HEADED!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "HOT HEADED!");
		break;
	case NimbleBones:
		Accolade_NimbleBonesCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("NIMBLE BONES!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "NIMBLE BONES!");
		break;
	case DeathDodger:
		Accolade_DeathDodgerCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("DEATH DODGER!"));
		//GEngine->AddOnScreenDebugMessage(-1 ,2.f, FColor::Green, "DEATH DODGER!");
		break;
	case PiratesFortitude:
		Accolade_PiratesFortitudeCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("PIRATES FORTITUDE!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "PIRATES FORTITUDE!");
		break;
	case PlunderersProwess:
		Accolade_PlunderersProwessCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("PLUNDERERS PROWESS!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "PLUNDERERS PROWESS!");
		break;
	case IPreferTreasure:
		Accolade_IPreferTreasureCount++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("I PREFER TREASURE!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "I PREFER TREASURE!");
		break;
	case PirateBlitz:
		Accolade_PirateBlitz++;
		PlayerCharacter->AnnounceAccolade(FText::FromString("PIRATE BLITZ!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "PIRATE BLITZ!");
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
