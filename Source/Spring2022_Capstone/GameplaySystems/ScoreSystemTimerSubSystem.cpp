// Created by Spring2022_Capstone team


#include "ScoreSystemTimerSubSystem.h"

#include "EnemyWaveManagementSystem.h"
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
			ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::SkullNCrosshair);
			StopAccoladeTimer(EAccolades::SkullNCrosshair);
		}
	}
}

void UScoreSystemTimerSubSystem::SetPlayerReference(APlayerCharacter* Player)
{
	PlayerCharacter = Player;
}

void UScoreSystemTimerSubSystem::SetWaveManagerReference(UEnemyWaveManagementSystem* WaveManagerInstance)
{
	WaveManager = WaveManagerInstance;
}

void UScoreSystemTimerSubSystem::IncrementCaptainOfWarKills()
{
	CaptainOfWarKills++;
	if(IsAccoladeTimerRunning(EAccolades::CaptainOfWar) && CaptainOfWarKills >= CAPTAIN_OF_WAR_KILL_REQUIREMENT)
	{
		ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::CaptainOfWar);
		StopAccoladeTimer(EAccolades::CaptainOfWar);
	}
}

void UScoreSystemTimerSubSystem::StartWave()
{
	bWaveStarted = true;
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

		
	// Wave Time Based Accolades
	if(bWaveStarted)
	{
		// Pirates Fortitude Accolade
		if(PlayerCharacter->GetCurrentHealth() >= PIRATES_FORTITUDE_HEALTH_PERCENTAGE / 100 * PlayerCharacter->GetMaxHealth())
			PiratesFortitudeTimeInRange += DeltaTime;
		// Plunderers Prowess Accolade
		if(PlayerCharacter->GetCurrentHealth() >= PLUNDERERS_PROWESS_HEALTH_PERCENTAGE / 100 * PlayerCharacter->GetMaxHealth())
			PlunderersProwessTimeInRange += DeltaTime;
	}
	// Sky Pirate Accolade
	if(bSkyPirateTimerStarted)
	{
		SkyPirateTimer += DeltaTime;
		if(SkyPirateTimer >= SKY_PIRATE_TIME_REQUIREMENT)
		{
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
	case CaptainsCoup:
		bCaptainsCoupTimerStarted = true;
		break;
	case PirateBlitz:
		bPirateBlitzTimerStarted = true;
		break;
	default: GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Accolade does not require a Timer");;
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
		break;
	case CaptainsCoup:
		bCaptainsCoupTimerStarted = false;
		CaptainsCoupTimer = 0.0f;
		break;
	case PirateBlitz:
		PirateBlitzTimer = false;
		PirateBlitzTimer = 0.0f;
		break;
	default: GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Accolade does not require a timer");;
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
	case CaptainsCoup:
		return bCaptainsCoupTimerStarted;
	case PirateBlitz:
		return bPirateBlitzTimerStarted;
	default: GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Accolade does not require a timer");
	}
	return false;
}

void UScoreSystemTimerSubSystem::FinishWave()
{
	// Pirate Blitz Accolade Check
	if(PirateBlitzTimer < PIRATE_BLITZ_TIME_REQUIREMENT)
	{
		ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::PirateBlitz);
		StopAccoladeTimer(EAccolades::PirateBlitz);
	}
	else
		StopAccoladeTimer(EAccolades::PirateBlitz);
	// Pirates Fortitude Accolade Check
	if(PiratesFortitudeTimeInRange >= WaveManager->GetElapsedWaveTime() / 2)
		ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::PiratesFortitude);
	
	// Plunderers Prowess Accolade Check
	if(PlunderersProwessTimeInRange >= WaveManager->GetElapsedWaveTime() / 2)
		ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::PlunderersProwess);

	// Reset wave timer based accolade properties.
	bWaveStarted = false;
	PiratesFortitudeTimeInRange = 0.0f;
	PlunderersProwessTimeInRange = 0.0f;
}


