// Copyright Epic Games, Inc. All Rights Reserved.

#include "Spring2022_CapstoneGameModeBase.h"

void ASpring2022_CapstoneGameModeBase::InitGameState()
{
	Super::InitGameState();

	//Check if no hard override is active
	if (DefaultPawnClass == ADefaultPawn::StaticClass())
	{
		//Update to custom implementation
		DefaultPawnClass = CustomPlayerPawnClass;
	}
}