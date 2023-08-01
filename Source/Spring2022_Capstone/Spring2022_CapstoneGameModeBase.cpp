// Copyright Epic Games, Inc. All Rights Reserved.


#include "Spring2022_CapstoneGameModeBase.h"

<<<<<<< Updated upstream
#include "Kismet/GameplayStatics.h"

void ASpring2022_CapstoneGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Create an instance of EnemyWaveManager BP assigned in the details panel. 
	EnemyWaveManagerInstance = NewObject<UEnemyWaveManagementSystem>(this, LevelEnemyWaveManagerBP);
	EnemyWaveManagerInstance->SetEnemySpawnLocations();
	
	GetWorld()->GetTimerManager().SetTimer(FirstWaveStartTimerHandle, this, &ASpring2022_CapstoneGameModeBase::SpawnWave, TimeBeforeFirstWave, false);
	
}

UEnemyWaveManagementSystem* ASpring2022_CapstoneGameModeBase::GetWaveManager()
{
	if(EnemyWaveManagerInstance)
		return EnemyWaveManagerInstance;
	else
		return nullptr;
}

void ASpring2022_CapstoneGameModeBase::SpawnWave()
{
	if(EnemyWaveManagerInstance)
		EnemyWaveManagerInstance->SpawnWave();
}
=======
void ASpring2022_CapstoneGameModeBase::IncrementKills()
{

	//Simple clamp function to ensure kills do not exceed the maximum possible kills. If max kills does not apply to your
	//game mode just comment this function and uncomment the other one.
	PlayerKills = FMath::Clamp(PlayerKills++, 0.0f, MaxPlayerKills);

	//PlayerKills++; //Uncomment this if max kills does not count

	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, FString::Printf(TEXT("Adding 1 to Player kills")));
}
>>>>>>> Stashed changes
