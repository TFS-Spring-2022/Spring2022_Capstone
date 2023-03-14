// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyPlayerController.h"
#include "GameFramework/DefaultPawn.h"
#include "Spring2022_CapstoneGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API ASpring2022_CapstoneGameModeBase : public AGameModeBase
{
GENERATED_BODY()
	
public:
	void InitGameState() override;

private:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<AMyPlayerController> CustomPlayerPawnClass = AMyPlayerController::StaticClass();

};
