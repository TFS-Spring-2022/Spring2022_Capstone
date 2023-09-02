// Created by Spring2022_Capstone team


#include "ScoreSystemTimerSubSystem.h"

#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

void UScoreSystemTimerSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ResetScoreSystemTimerSubSystem();
}

void UScoreSystemTimerSubSystem::SetScoreManagerSubSystem(UScoreSystemManagerSubSystem* SubSystem)
{
	ScoreManagerSubSystem = SubSystem;
}

void UScoreSystemTimerSubSystem::IncrementScullNCrosshairHeadshotHits()
{
	if(bSkullNCrosshairTimerStarted)
	{
		SkullNCrosshairHeadshotHits++;
		if(SkullNCrosshairHeadshotHits >= SKULL_N_CROSSHAIR_HEADSHOT_REQUIREMENT)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "SKULL N CROSSHAIR!");
			ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::SkullNCrosshair);
			StopAccoladeTimer(EAccolades::SkullNCrosshair);
		}
	}
}

void UScoreSystemTimerSubSystem::SetPlayerReference(APlayerCharacter* Player)
{
	PlayerCharacter = Player;
}

void UScoreSystemTimerSubSystem::IncrementCaptainOfWarKills()
{
	CaptainOfWarKills++;
	if(IsAccoladeTimerRunning(EAccolades::CaptainOfWar) && CaptainOfWarKills >= CAPTAIN_OF_WAR_KILL_REQUIREMENT)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "CAPTAIN OF WAR!");
		ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::CaptainOfWar);
		StopAccoladeTimer(EAccolades::CaptainOfWar);
	}
}

void UScoreSystemTimerSubSystem::ResetScoreSystemTimerSubSystem()
{
	bSkyPirateTimerStarted = false;
	SkyPirateTimer = 0.0f;
	bLandLubberTimerStarted = false;
	LandLubberTimer = 0.0f;
	bPirateBlitzTimerStarted = false;
	PirateBlitzTimer = 0.0f;
}

void UScoreSystemTimerSubSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!ScoreManagerSubSystem || !PlayerCharacter)
		return;

	// Sky Pirate Accolade
	if(bSkyPirateTimerStarted)
	{
		SkyPirateTimer += DeltaTime;
		if(SkyPirateTimer >= SKY_PIRATE_TIME_REQUIREMENT)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "SKY PIRATE!");
			ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::SkyPirate);
			StopAccoladeTimer(EAccolades::SkyPirate);
		}
	}
	// Land Lubber Accolade
	if(bLandLubberTimerStarted)
	{
		LandLubberTimer += DeltaTime;
		if(LandLubberTimer >= LAND_LUBBER_TIME_REQUIREMENT)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "LAND LUBBER!");
			ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::LandLubber);
			StopAccoladeTimer(EAccolades::LandLubber);
		}
	}
	// Pirate Blitz Accolade
	if(bPirateBlitzTimerStarted)
		PirateBlitzTimer += DeltaTime;
	// Captains Coup Accolade
	if(bCaptainsCoupTimerStarted)
	{
		CaptainsCoupTimer += DeltaTime;
		if(CaptainsCoupTimer >= CAPTAINS_COUP_TIME_REQUIREMENT)
			StopAccoladeTimer(EAccolades::CaptainsCoup);
	}
	// SkullNCrosshair Accolade
	if(bSkullNCrosshairTimerStarted)
	{
		SkullNCrosshairTimer += DeltaTime;
		if(SkullNCrosshairTimer >= SKULL_N_CROSSHAIR_TIME_REQUIREMENT)
			StopAccoladeTimer(EAccolades::SkullNCrosshair);
	}
	// Close Call Corsair Accolade
	if(bCloseCallCorsairTimerStarted)
	{
		CloseCallCorsairTimer += DeltaTime;
		float PlayersCurrentHealth = PlayerCharacter->GetCurrentHealth();
		float TotalHealthLost = CloseCallCorsairHealthEntryPoint - PlayersCurrentHealth;
		if(TotalHealthLost >= CloseCallCorsairHealthTarget)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "CLOSE CALL CORSAIR!");
			ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::CloseCallCorsair);
			StopAccoladeTimer(EAccolades::CloseCallCorsair);
		}
		if(CloseCallCorsairTimer >= CLOSE_CALL_CORSAIR_TIME_REQUIREMENT)
			StopAccoladeTimer(EAccolades::CloseCallCorsair);
	}
	// Captain Of War Accolade
	if(bCaptainOfWarTimerStarted)
	{
		CaptainOfWarTimer += DeltaTime;
		if(CaptainOfWarTimer >= CAPTAIN_OF_WAR_TIME_REQUIREMENT)
			StopAccoladeTimer(EAccolades::CaptainOfWar);
	}
		
	
}

void UScoreSystemTimerSubSystem::StartAccoladeTimer(EAccolades Accolade)
{
	switch (Accolade)
	{
	case SkullNCrosshair:
		bSkullNCrosshairTimerStarted = true;
		IncrementScullNCrosshairHeadshotHits(); // Called to ensure first hit is recorded.
		break;
	case CaptainOfWar:
		bCaptainOfWarTimerStarted = true;
		IncrementCaptainOfWarKills(); // Called to ensure first kill is recorded. ToDo: Can probably remove this when refactored.
		break;
	case SkyPirate: 
		bSkyPirateTimerStarted = true;
		break;
	case LandLubber:
		bLandLubberTimerStarted = true;
		break;
	case CloseCallCorsair:
		CloseCallCorsairHealthTarget = CLOSE_CALL_CORSAIR_HEALTH_PERCENTAGE / 100 * PlayerCharacter->GetMaxHealth();
		CloseCallCorsairHealthEntryPoint = PlayerCharacter->GetCurrentHealth();
		bCloseCallCorsairTimerStarted = true;
		break;
	case Opportunist: break;
	case CaptainsCoup:
		bCaptainsCoupTimerStarted = true;
		break;
	case DoubleAerialPlunder: break;
	case BlunderBlast: break;
	case SkyBuccaneer: break;
	case CoolHeaded: break;
	case NimbleBones: break;
	case DeathDodger: break;
	case PiratesFortitude: break;
	case PlunderersProwess: break;
	case IPreferTreasure: break;
	case PirateBlitz:
		bPirateBlitzTimerStarted = true;
		break;
	default: ;
	}
}

void UScoreSystemTimerSubSystem::StopAccoladeTimer(EAccolades Accolade)
{
	switch (Accolade)
	{
	case SkullNCrosshair:
		bSkullNCrosshairTimerStarted = false;
		SkullNCrosshairTimer = 0.0f;
		SkullNCrosshairHeadshotHits = 0;
		break;
	case CaptainOfWar:
		bCaptainOfWarTimerStarted = false;
		CaptainOfWarTimer = 0.0f;
		CaptainOfWarKills = 0;
		break;
	case SkyPirate:
		bSkyPirateTimerStarted = false;
		SkyPirateTimer = 0.0f;
		break;
	case LandLubber:
		bLandLubberTimerStarted = false;
		LandLubberTimer = 0.0f;
		break;
	case CloseCallCorsair:
		bCloseCallCorsairTimerStarted = false;
		CloseCallCorsairTimer = 0.0f;
		// ToDo: What exactly do I clear here?
		break;
	case Opportunist: break;
	case CaptainsCoup:
		bCaptainsCoupTimerStarted = false;
		CaptainsCoupTimer = 0.0f;
		break;
	case DoubleAerialPlunder: break;
	case BlunderBlast: break;
	case SkyBuccaneer: break;
	case CoolHeaded: break;
	case NimbleBones: break;
	case DeathDodger: break;
	case PiratesFortitude: break;
	case PlunderersProwess: break;
	case IPreferTreasure: break;
	case PirateBlitz:
		PirateBlitzTimer = false;
		PirateBlitzTimer = 0.0f;
		break;
	default: ;
	}
}

bool UScoreSystemTimerSubSystem::IsAccoladeTimerRunning(EAccolades Accolade)
{
	switch (Accolade)
	{
	case SkullNCrosshair:
		return bSkullNCrosshairTimerStarted;
	case CaptainOfWar: 
		return bCaptainOfWarTimerStarted;
	case SkyPirate:
		return bSkyPirateTimerStarted;
	case LandLubber:
		return bLandLubberTimerStarted;
	case CloseCallCorsair:
		return bCloseCallCorsairTimerStarted;
	case Opportunist: break;
	case CaptainsCoup:
		return bCaptainsCoupTimerStarted;
	case DoubleAerialPlunder: break;
	case BlunderBlast: break;
	case SkyBuccaneer: break;
	case CoolHeaded: break;
	case NimbleBones: break;
	case DeathDodger: break;
	case PiratesFortitude: break;
	case PlunderersProwess: break;
	case IPreferTreasure: break;
	case PirateBlitz:
		return bPirateBlitzTimerStarted;
	default:;
	}
	return false;
}

void UScoreSystemTimerSubSystem::FinishWave()
{
	// Pirate Blitz Accolade Check
	if(PirateBlitzTimer < PIRATE_BLITZ_TIME_REQUIREMENT)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "PIRATE BLITZ");
		ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::PirateBlitz);
		StopAccoladeTimer(EAccolades::PirateBlitz);
	}
	else
		StopAccoladeTimer(EAccolades::PirateBlitz);
}


