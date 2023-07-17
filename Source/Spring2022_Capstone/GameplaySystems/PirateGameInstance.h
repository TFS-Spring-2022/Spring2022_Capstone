// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Spring2022_Capstone/Sounds/Sound_Manager.h"
#include "PirateGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API UPirateGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	ASound_Manager* GetSoundManager() const;

private:
	UPROPERTY(EditAnywhere, Category = Sounds)
	ASound_Manager* SoundManagerInstance;
	
};


