// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SoundManagerSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API USoundManagerSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	

public:
	USoundManagerSubSystem();
	
	UFUNCTION()
	void PlaySound(const FVector& Location, USoundBase* Sound) const;

	UFUNCTION()
	void PlaysMusic(const USoundCue* Music) const;

	UPROPERTY(EditAnywhere, Category = "Menu Music")
	USoundCue* MainMenuMusic;

	UPROPERTY(EditAnywhere, Category = "Menu sounds")
	USoundCue* HoverButtonSound;

	UPROPERTY(EditAnywhere, Category = "Menu sounds")
	USoundCue* ClickButtonSound;

	
};
