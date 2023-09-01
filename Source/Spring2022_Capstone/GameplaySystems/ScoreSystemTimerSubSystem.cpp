// Created by Spring2022_Capstone team


#include "ScoreSystemTimerSubSystem.h"

void UScoreSystemTimerSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UScoreSystemTimerSubSystem::SetScoreManagerSubSystem(UScoreSystemManagerSubSystem* SubSystem)
{
	ScoreManagerSubSystem = SubSystem;
}

void UScoreSystemTimerSubSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!ScoreManagerSubSystem)
		return;

	// Land Lubber Accolade
	if(bSkyPirateTimerStarted)
	{
		SkyPirateTimer+=DeltaTime;
		if(SkyPirateTimer >= SKY_PIRATE_TIME_REQUIREMENT)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "SKY PIRATE!");
			ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::SkyPirate);
			bSkyPirateTimerStarted = false;
			StopAccoladeTimer(EAccolades::SkyPirate);
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
	case LandLubber: break;
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
	case LandLubber: break;
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
