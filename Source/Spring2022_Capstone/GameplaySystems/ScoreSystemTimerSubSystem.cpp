// Created by Spring2022_Capstone team


#include "ScoreSystemTimerSubSystem.h"

void UScoreSystemTimerSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ResetScoreSystemTimerSubSystem();
}

void UScoreSystemTimerSubSystem::SetScoreManagerSubSystem(UScoreSystemManagerSubSystem* SubSystem)
{
	ScoreManagerSubSystem = SubSystem;
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

	if(!ScoreManagerSubSystem)
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

}

void UScoreSystemTimerSubSystem::StartAccoladeTimer(EAccolades Accolade)
{
	switch (Accolade)
	{
	case SkullNCrosshair: break;
	case CaptainOfWar: break;
	case SkyPirate: 
		bSkyPirateTimerStarted = true;
		break;
	case LandLubber:
		bLandLubberTimerStarted = true;
		break;
	case CloseCallCorsair: break;
	case Opportunist: break;
	case CaptainsCoup: break;
	case DoubleAerialPlunder: break;
	case BlunderBlast: break;
	case SkyBuccaneer: break;
	case CoolHeaded: break;
	case NimbleBones: break;
	case DeathDodger: break;
	case PiratesFortitude: break;
	case PlunderersProwess: break;
	case IPreferTreasure: break;
	case PirateBlitz: break;
	default: ;
	}
}

void UScoreSystemTimerSubSystem::StopAccoladeTimer(EAccolades Accolade)
{
	switch (Accolade)
	{
	case SkullNCrosshair: break;
	case CaptainOfWar: break;
	case SkyPirate:
		bSkyPirateTimerStarted = false;
		SkyPirateTimer = 0.0f;
		break;
	case LandLubber:
		bLandLubberTimerStarted = false;
		LandLubberTimer = 0.0f;
		break;
	case CloseCallCorsair: break;
	case Opportunist: break;
	case CaptainsCoup: break;
	case DoubleAerialPlunder: break;
	case BlunderBlast: break;
	case SkyBuccaneer: break;
	case CoolHeaded: break;
	case NimbleBones: break;
	case DeathDodger: break;
	case PiratesFortitude: break;
	case PlunderersProwess: break;
	case IPreferTreasure: break;
	case PirateBlitz: break;
	default: ;
	}
}

bool UScoreSystemTimerSubSystem::IsAccoladeTimerRunning(EAccolades Accolade)
{
	switch (Accolade)
	{
	case SkullNCrosshair: break;
	case CaptainOfWar: break;
	case SkyPirate:
		return bSkyPirateTimerStarted;
		break;
	case LandLubber:
		return bLandLubberTimerStarted;
		break;
	case CloseCallCorsair: break;
	case Opportunist: break;
	case CaptainsCoup: break;
	case DoubleAerialPlunder: break;
	case BlunderBlast: break;
	case SkyBuccaneer: break;
	case CoolHeaded: break;
	case NimbleBones: break;
	case DeathDodger: break;
	case PiratesFortitude: break;
	case PlunderersProwess: break;
	case IPreferTreasure: break;
	case PirateBlitz: break;
	default:;
	}
	return false;
}
