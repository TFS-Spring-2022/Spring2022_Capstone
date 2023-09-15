// Created by Spring2022_Capstone team


#include "EnemyWaveManagementSystem.h"

#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/Spring2022_CapstoneGameModeBase.h"


UEnemyWaveManagementSystem::UEnemyWaveManagementSystem()
{
}

void UEnemyWaveManagementSystem::BeginPlay()
{
	Super::BeginPlay();

	const UGameInstance *GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	SoundManagerSubSystem = GameInstance->GetSubsystem<USoundManagerSubSystem>();
	
	PrimaryComponentTick.Target = this;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(true);
	PrimaryComponentTick.RegisterTickFunction(GetComponentLevel());
	
	// Create Wave Announcer Widget and apply to screen.
	if(WaveAnnouncerWidgetBP)
	{
		WaveAnnouncerWidgetInstance = Cast<UWaveAnnouncerWidget>(CreateWidget(GetWorld(), WaveAnnouncerWidgetBP));
		WaveAnnouncerWidgetInstance->AddToViewport(1);
	}

	bEliteEnemySpawnedThisWave = false;
	EnemiesKilledThisWave = 0;
}

void UEnemyWaveManagementSystem::SetEnemySpawnLocations()
{
	// ToDo: Add EnemySpawnPoints to array from EnemySpawnPoint::BeginPlay() (beware execution order).
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnPoint::StaticClass(), EnemySpawnLocations);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASniperEnemy::StaticClass(), SniperEnemies);
}

void UEnemyWaveManagementSystem::SpawnWave()
{
	// Reset wave stats.
	EnemiesKilledThisWave = 0;

	// Announce wave to player.
	if(WaveAnnouncerWidgetInstance)
		WaveAnnouncerWidgetInstance->SetAnnouncementTextBlock(FText::FromString(FString::Printf(TEXT("WAVE %d"), CurrentWave + 1)));
	
	// Restart wave timer on new wave.
	ElapsedWaveTime = 0.0f;
	WaveTimerMinutes = 0;
	WaveTimerSeconds = 0.0f;

	//Sounds
	SoundManagerSubSystem->ResetEventTokens();
	if(SoundManagerSubSystem)
	{
		SoundManagerSubSystem->WaveStart(PlayerCharacter);
		SoundManagerSubSystem->ToggleMusicOn(PlayerCharacter->MusicAudioComp);
		GetWorld()->GetTimerManager().SetTimer(TimeBeforeWaveStartVoiceLine,this,&UEnemyWaveManagementSystem::PlayWaveStartVoiceLine, 2.f,false);
	}
	
	// Assigning here due to execution order.
	if(!ScoreSystemTimerSubSystem)
		ScoreSystemTimerSubSystem = GetWorld()->GetSubsystem<UScoreSystemTimerSubSystem>();
	
	// Check for Pirate Blitz Accolade
	if(ScoreSystemTimerSubSystem)
	{
		ScoreSystemTimerSubSystem->SetWaveManagerReference(this);
		ScoreSystemTimerSubSystem->StartWave();
		
		if(ScoreSystemTimerSubSystem->IsAccoladeTimerRunning(EAccolades::PirateBlitz) == false)
			ScoreSystemTimerSubSystem->StartAccoladeTimer(EAccolades::PirateBlitz);
	}

	// If we have passed all the waves.
	if(CurrentWave > Waves.Num() - 1)
	{
		Cast<ASpring2022_CapstoneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->EndRun(); 
		return;
	}

	float TimeBetweenSpawns = MINIMUM_TIME_BETWEEN_SPAWNS;
	
	for (TSubclassOf<ABaseEnemy> EnemyToSpawn : Waves[CurrentWave].EnemiesToSpawn)
	{
		// Spawn Enemies on a delay.
		FTimerHandle SpawnCallTimerHandle;
		FTimerDelegate SpawnEnemyDelegate = FTimerDelegate::CreateUObject(this, &UEnemyWaveManagementSystem::SpawnEnemy, EnemyToSpawn);
		const float DelayTime = TimeBetweenSpawns + FMath::RandRange(SPAWN_DELAY_MINIMUM_BUFFER, SPAWN_DELAY_MAXIMUM_BUFFER);
		GetWorld()->GetTimerManager().SetTimer(SpawnCallTimerHandle, SpawnEnemyDelegate, DelayTime, false);
		TimeBetweenSpawns += MINIMUM_TIME_BETWEEN_SPAWNS;
	}

	// Enable all snipers
	for (AActor* Sniper : SniperEnemies)
	{
		Cast<ASniperEnemy>(Sniper)->EnableSniperEnemy();
	}
	
	// Set remaining enemies text to the amount in the current wave.
	PlayerCharacter->GetPlayerHUD()->SetEnemiesRemainingText(Waves[CurrentWave].EnemiesToSpawn.Num());

	//CurrentWave++;
}

void UEnemyWaveManagementSystem::SpawnEnemy(TSubclassOf<ABaseEnemy> SpawningEnemy)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
	int RandomSpawnSelection = FMath::RandRange(0, EnemySpawnLocations.Num()-1);

	// Don't spawn at same point twice to avoid enemy overlap.
	do
	{
		RandomSpawnSelection = FMath::RandRange(0, EnemySpawnLocations.Num()-1);
	}
	while (RandomSpawnSelection == LastSpawnLocationElement);

	LastSpawnLocationElement = RandomSpawnSelection;
		
	FVector Location = EnemySpawnLocations[RandomSpawnSelection]->GetActorLocation();
	FRotator Rotation = EnemySpawnLocations[RandomSpawnSelection]->GetActorRotation();
		
	AActor* SpawnedEnemy = GetWorld()->SpawnActor(SpawningEnemy, &Location, &Rotation, SpawnParams);
	ActiveEnemies.Add(SpawnedEnemy);
	EnemiesToDestroy.Add(SpawnedEnemy);

	// Elite spawning
	if(CurrentWave > 0 && !bEliteEnemySpawnedThisWave)
	{
		if(ABaseEnemy* EnemyToPromote = Cast<ABaseEnemy>(SpawnedEnemy))
		{
			EnemyToPromote->PromoteToElite();
			bEliteEnemySpawnedThisWave = true;
		}
	}
}

void UEnemyWaveManagementSystem::RemoveActiveEnemy(AActor* EnemyToRemove)
{
	if(ActiveEnemies.Contains(EnemyToRemove))
	{
		EnemiesKilledThisWave++;
		
		ActiveEnemies.Remove(EnemyToRemove);
		// Update enemies remaining text.
		//PlayerCharacter->GetPlayerHUD()->SetEnemiesRemainingText(ActiveEnemies.Num());
		PlayerCharacter->GetPlayerHUD()->SetEnemiesRemainingText(Waves[CurrentWave].EnemiesToSpawn.Num() - EnemiesKilledThisWave);

		// ROUND IS DONE
		// Note - This is inside the if-contains to prevent placed enemies out of ActiveEnemies[]
		// from spawning an unwanted wave.
		if(ActiveEnemies.IsEmpty())
		{
			CurrentWave++;
			
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

void UEnemyWaveManagementSystem::ConvertWaveTime(float DTime)
{
	WaveTimerSeconds += DTime;
	if(WaveTimerSeconds >= 60)
	{
		WaveTimerMinutes++;
		WaveTimerSeconds = 0;
	}

	if(!PlayerCharacter)
	{
		PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		return;
	}
	
	PlayerCharacter->GetPlayerHUD()->SetWaveTimerText(WaveTimerMinutes, WaveTimerSeconds);
}

void UEnemyWaveManagementSystem::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ElapsedWaveTime += DeltaTime;
	ConvertWaveTime(DeltaTime);
}

float UEnemyWaveManagementSystem::GetElapsedWaveTime() const
{
	return ElapsedWaveTime;
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
	if(ScoreSystemTimerSubSystem)
		ScoreSystemTimerSubSystem->FinishWave();
	
	// Assigning here due to execution order.
	if(!ScoreSystemManagerSubSystem)
		ScoreSystemManagerSubSystem = GetWorld()->GetGameInstance()->GetSubsystem<UScoreSystemManagerSubSystem>();

	// Check for wave end accolades
	if(ScoreSystemManagerSubSystem)
		ScoreSystemManagerSubSystem->CheckWaveEndAccolades();

	bEliteEnemySpawnedThisWave = false; // Reset EliteEnemySpawning bool.
	GetWorld()->GetTimerManager().SetTimer(TimeBeforeUpgradeMenuTimerHandle, this, &UEnemyWaveManagementSystem::SpawnWave, TimeBeforeNextRoundStart, false);
}

void UEnemyWaveManagementSystem::PlayWaveStartVoiceLine() const
{
	if(SoundManagerSubSystem)
	{
		if(FMath::RandRange(1,2) == 1)
			SoundManagerSubSystem->PlayNarratorSoundEvent(PlayerCharacter->PlayerVoiceAudioComp, 9);
		else
			SoundManagerSubSystem->PlayPlayerSoundEvent(PlayerCharacter->PlayerVoiceAudioComp, 7);
	}
}
