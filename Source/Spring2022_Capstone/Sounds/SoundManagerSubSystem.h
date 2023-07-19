// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
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
	
};
