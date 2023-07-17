// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Spring2022_Capstone/Sounds/Sound_Manager.h"
#include "SkyPirateGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API ASkyPirateGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION()
	ASound_Manager* GetSoundManager() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	ASound_Manager* SoundManagerInstance;

	
};
