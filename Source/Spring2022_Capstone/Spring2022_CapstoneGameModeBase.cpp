// Copyright Epic Games, Inc. All Rights Reserved.


#include "Spring2022_CapstoneGameModeBase.h"

#include "Enemies/AIAttackSystemComponent.h"
#include "Kismet/GameplayStatics.h"

void ASpring2022_CapstoneGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Create an instance of EnemyWaveManager BP assigned in the details panel. 
	EnemyWaveManagerInstance = NewObject<UEnemyWaveManagementSystem>(this, LevelEnemyWaveManagerBP);
	EnemyWaveManagerInstance->SetEnemySpawnLocations();
	EnemyWaveManagerInstance->RegisterComponent();
	
	SoundManagerSubSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<USoundManagerSubSystem>();
	
	AIAttackSystemComp = FindComponentByClass<UAIAttackSystemComponent>();
	if(!AIAttackSystemComp)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No AIAttackSystemComponent On Game Mode BP");
	
	GetWorld()->GetTimerManager().SetTimer(FirstWaveStartTimerHandle, this, &ASpring2022_CapstoneGameModeBase::SpawnWave, TimeBeforeFirstWave, false);
	

	if(!PlayerCharacter)
		PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	SoundManagerSubSystem->ToggleMusicOn(PlayerCharacter->MusicAudioComp);
}

UEnemyWaveManagementSystem* ASpring2022_CapstoneGameModeBase::GetWaveManager()
{
	if(EnemyWaveManagerInstance)
		return EnemyWaveManagerInstance;
	else
		return nullptr;
}

UAIAttackSystemComponent* ASpring2022_CapstoneGameModeBase::GetAttackSystemComponent()
{
	if(AIAttackSystemComp)
		return AIAttackSystemComp;
	else
		return nullptr;
}

void ASpring2022_CapstoneGameModeBase::SpawnWave()
{
	if(EnemyWaveManagerInstance)
		EnemyWaveManagerInstance->SpawnWave();
	// Ensure token is not lost between waves.
	if(AIAttackSystemComp)
		AIAttackSystemComp->ReturnToken();
}

void ASpring2022_CapstoneGameModeBase::EndRun() const
{
	// ToDo: Move to scoring/accolades end screen
	UGameplayStatics::OpenLevel(this, "RunEndScreenLevel");
}
