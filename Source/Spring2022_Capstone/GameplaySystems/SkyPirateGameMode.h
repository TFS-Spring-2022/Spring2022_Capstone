// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SkyPirateGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API ASkyPirateGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASkyPirateGameMode();
	
	virtual void BeginPlay() override;
	
};
