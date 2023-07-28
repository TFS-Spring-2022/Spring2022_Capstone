// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyWaveManagementSystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SPRING2022_CAPSTONE_API UEnemyWaveManagementSystem : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category = "DEBUG")
	float DEBUG_FloatValue;
	
	// Using to test, just prints to UE_Log the value of DEBUG_FloatValue.
	void DEBUG_PublicCall();
	
};
