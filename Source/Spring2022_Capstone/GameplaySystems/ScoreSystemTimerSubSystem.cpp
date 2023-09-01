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
	if(bLandLubberTimerStarted)
	{
		LandLubberTimer+=DeltaTime;
		if(LandLubberTimer >= LAND_LUBBER_TIME_REQUIREMENT)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "LAND LUBBER!");
			ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::LandLubber);
			bLandLubberTimerStarted = false;
		}
	}
	else
		LandLubberTimer = 0.0f;
}


void UScoreSystemTimerSubSystem::StartLandLubberTimer()
{
	bLandLubberTimerStarted = true;
}

void UScoreSystemTimerSubSystem::StopLandLubberTImer()
{
	bLandLubberTimerStarted = false;
	LandLubberTimer = 0.0f;
}
