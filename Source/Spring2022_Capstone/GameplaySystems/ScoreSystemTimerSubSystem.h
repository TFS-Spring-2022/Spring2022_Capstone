// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "ScoreSystemManagerSubSystem.h"
#include "Subsystems/WorldSubsystem.h"
#include "ScoreSystemTimerSubSystem.generated.h"

/**
 * A TickableWorldSubsystem used to communicate with the ScoreSystemManagerSubsystem and handle awarding
 * time based accolades.
 */
UCLASS()
class SPRING2022_CAPSTONE_API UScoreSystemTimerSubSystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Tick(float DeltaTime) override;

	// Required to run
	virtual TStatId GetStatId() const override
	{
		return GetStatID();
	}

	// Reference to the ScoreSystemManagerSubSystem, set from UScoreSystemManagerSubSystem::Initialize().
	UPROPERTY()
	UScoreSystemManagerSubSystem* ScoreManagerSubSystem;

public:

	void SetScoreManagerSubSystem(UScoreSystemManagerSubSystem* SubSystem);

	// Starts the timer for the given accolade.
	void StartAccoladeTimer(EAccolades Accolade);
	// Stops and clears the timer for the given accolade.
	void StopAccoladeTimer(EAccolades Accolade);
	// Returns the status of the accolade timer.
	bool IsAccoladeTimerRunning(EAccolades Accolade);

	bool bSkyPirateTimerStarted;
	float SkyPirateTimer = 0.0f;

	bool bLandLubberTimerStarted;
	float LandLubberTimer = 0.0f;

private:

	// Accolade Time Requirements:
	const float SKY_PIRATE_TIME_REQUIREMENT = 5.0f; // ToDo: 10/15 in actuality just going to put 5.0f for testing/showing.
	const float LAND_LUBBER_TIME_REQUIREMENT = 15.0f;
	
};
