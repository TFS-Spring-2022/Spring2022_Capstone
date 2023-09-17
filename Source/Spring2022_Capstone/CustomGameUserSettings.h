// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "CustomGameUserSettings.generated.h"

/**
 *
 */
UCLASS()
class SPRING2022_CAPSTONE_API UCustomGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UCustomGameUserSettings();

	UFUNCTION(BlueprintCallable)
	static UCustomGameUserSettings *GetCustomGameUserSettings();

	UPROPERTY(Config, BlueprintReadWrite)
	float YSensitivity;
	UPROPERTY(Config, BlueprintReadWrite)
	float XSensitivity;
	
	UPROPERTY(Config, BlueprintReadWrite)
	float MasterVolumeValue;
	UPROPERTY(Config, BlueprintReadWrite)
	float SFXVolumeValue;
	UPROPERTY(Config, BlueprintReadWrite)
	float MusicVolumeValue;
	UPROPERTY(Config, BlueprintReadWrite)
	float VoiceVolumeValue;
};
