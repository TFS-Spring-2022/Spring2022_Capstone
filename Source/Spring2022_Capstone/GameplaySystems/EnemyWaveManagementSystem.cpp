// Created by Spring2022_Capstone team


#include "EnemyWaveManagementSystem.h"

#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/Spring2022_CapstoneGameModeBase.h"


void UEnemyWaveManagementSystem::SetEnemySpawnLocations()
{
	// ToDo: Add EnemySpawnPoints to array from EnemySpawnPoint::BeginPlay() (beware execution order).
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnPoint::StaticClass(), EnemySpawnLocations);
}

void UEnemyWaveManagementSystem::SpawnWave()
{
	// Assigning here due to execution order.
	if(!ScoreSystemTimerSubSystem)
		ScoreSystemTimerSubSystem = GetWorld()->GetSubsystem<UScoreSystemTimerSubSystem>();

	// Check for Pirate Blitz Accolade
	if(ScoreSystemTimerSubSystem)
	{
		if(ScoreSystemTimerSubSystem->IsAccoladeTimerRunning(EAccolades::PirateBlitz))
			ScoreSystemTimerSubSystem->FinishWave();
		else
			ScoreSystemTimerSubSystem->StartAccoladeTimer(EAccolades::PirateBlitz);
	}
	
	bool bEliteEnemySpawned = false;
	
	if(CurrentWave > Waves.Num() - 1)
	{
		Cast<ASpring2022_CapstoneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->EndRun(); 
		return;
	}
	
	for (TSubclassOf<ABaseEnemy> EnemyToSpawn : Waves[CurrentWave].EnemiesToSpawn)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		int RandomSpawnSelection = FMath::RandRange(0, EnemySpawnLocations.Num()-1);

		// ToDo: Temporary before spawning finalization.
		// Don't spawn at same point twice to avoid enemy overlap.
		do
		{
			RandomSpawnSelection = FMath::RandRange(0, EnemySpawnLocations.Num()-1);
		}
		while (RandomSpawnSelection == LastSpawnLocationElement);

		LastSpawnLocationElement = RandomSpawnSelection;
		
		FVector Location = EnemySpawnLocations[RandomSpawnSelection]->GetActorLocation();
		FRotator Rotation = EnemySpawnLocations[RandomSpawnSelection]->GetActorRotation();
		
		AActor* SpawnedEnemy = GetWorld()->SpawnActor(EnemyToSpawn, &Location, &Rotation, SpawnParams);
		ActiveEnemies.Add(SpawnedEnemy);
		EnemiesToDestroy.Add(SpawnedEnemy);

		// Elite spawning
		if(CurrentWave > 0 && !bEliteEnemySpawned)
		{
			if(ABaseEnemy* EnemyToPromote = Cast<ABaseEnemy>(SpawnedEnemy))
			{
				EnemyToPromote->PromoteToElite();
				bEliteEnemySpawned = true;
			}
		}
	}
	
	CurrentWave++;
}

void UEnemyWaveManagementSystem::RemoveActiveEnemy(AActor* EnemyToRemove)
{
	if(ActiveEnemies.Contains(EnemyToRemove))
	{
		ActiveEnemies.Remove(EnemyToRemove);
		
		// Note - This is inside the if-contains to prevent placed enemies out of ActiveEnemies[]
		// from spawning an unwanted wave.
		if(ActiveEnemies.IsEmpty())
		{
			// Begin play is not called on this component so PlayerCharacter must be set here.
			if(!PlayerCharacter)
				PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

			// Start next round after a delay, opens upgrade menu, clears enemy, and spawns next wave.
			GetWorld()->GetTimerManager().SetTimer(TimeBeforeNextRoundStartTimerHandle, this, &UEnemyWaveManagementSystem::OpenUpgradeMenu, TimeBeforeNextRoundStart, false);
			GetWorld()->GetTimerManager().SetTimer(TimeBeforeClearDeadEnemiesTimerHandle, this, &UEnemyWaveManagementSystem::ClearDeadEnemies, TimeBeforeNextRoundStart - 0.1, false);
			StartNextRound();
		}
	}
}

void UEnemyWaveManagementSystem::OpenUpgradeMenu() const
{
	PlayerCharacter->GetUpgradeSystemComponent()->OpenUpgradeMenu();
}

void UEnemyWaveManagementSystem::ClearDeadEnemies()
{

	for (AActor* DeadEnemy : EnemiesToDestroy)
	{
		DeadEnemy->Destroy();
	}

	// Without this line corpses will randomly not destroy.
	EnemiesToDestroy.Empty(); 
}

void UEnemyWaveManagementSystem::StartNextRound()
{
	// Assigning here due to execution order.
	if(!ScoreSystemManagerSubSystem)
		ScoreSystemManagerSubSystem = GetWorld()->GetGameInstance()->GetSubsystem<UScoreSystemManagerSubSystem>();

	// Check for wave end accolades
	if(ScoreSystemManagerSubSystem)
		ScoreSystemManagerSubSystem->CheckWaveEndAccolades();
	
	GetWorld()->GetTimerManager().SetTimer(TimeBeforeUpgradeMenuTimerHandle, this, &UEnemyWaveManagementSystem::SpawnWave, TimeBeforeNextRoundStart, false);
}
