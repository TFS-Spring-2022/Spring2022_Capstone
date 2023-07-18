// Created by Spring2022_Capstone team


#include "SkyPirateGameMode.h"

ASkyPirateGameMode::ASkyPirateGameMode()
{
	SoundManagerInstance = CreateDefaultSubobject<ASound_Manager>("SoundManagerInstance");
}

void ASkyPirateGameMode::BeginPlay()
{
	Super::BeginPlay();
	SoundManagerInstance = GetWorld()->SpawnActor<ASound_Manager>();
}

ASound_Manager* ASkyPirateGameMode::GetSoundManager() const
{
	return SoundManagerInstance;
}


