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
		}
	}
	else
		SkyPirateTimer = 0.0f;
}


void UScoreSystemTimerSubSystem::StartSkyPirateTimer()
{
	bSkyPirateTimerStarted = true;
}

void UScoreSystemTimerSubSystem::StopSkyPirateTimer()
{
	bSkyPirateTimerStarted = false;
	SkyPirateTimer = 0.0f;
}
