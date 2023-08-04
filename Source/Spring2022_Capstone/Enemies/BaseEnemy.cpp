// Created by Spring2022_Capstone team

#include "BaseEnemy.h"
#include "Spring2022_Capstone/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Spring2022_Capstone/Spring2022_CapstoneGameModeBase.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEnemy::Attack()
{
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEnemy::DamageActor(AActor *DamagingActor, const float DamageAmount)
{
	IDamageableActor::DamageActor(DamagingActor, DamageAmount);
	if (HealthComp)
	{
		HealthComp->SetHealth(HealthComp->GetHealth() - DamageAmount);
		if(HealthComp->GetHealth() <= 0)
		{
			
			Death();
		}
	}
}

void ABaseEnemy::Death()
{
	float TotalProbability = 0.f;
	for (float Probability : SpawnProbabilities)
	{
		TotalProbability += Probability;
	}

	//  grabs the percentage
	float RandomValue = FMath::FRandRange(0.f, 1.f);

	
	if (RandomValue <= TotalProbability)
	{
		// If drops are within chance this will make it drop
		float CurrentProbability = 0.f;
		for (int32 Index = 0; Index < SpawnableActors.Num(); Index++)
		{
			CurrentProbability += SpawnProbabilities[Index];
			if (RandomValue <= CurrentProbability)
			{
				// Spawn the chosen actor
				UWorld* World = GetWorld();
				if (World && SpawnableActors[Index])
				{
					FVector SpawnLocation = GetActorLocation();
					FRotator SpawnRotation = GetActorRotation();
					AActor* SpawnedActor = World->SpawnActor<AActor>(SpawnableActors[Index], SpawnLocation, SpawnRotation);
				}
				break;
			}
		}
	}
	// ToDo: Rag doll enemy once new skeleton is implemented.
	// Remove enemy from the wave manager (RemoveActiveEnemy() will only remove enemies inside ActiveEnemies[] in the Wave Manager). 
	UEnemyWaveManagementSystem* WaveManager = Cast<ASpring2022_CapstoneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetWaveManager();
	if(WaveManager)
		WaveManager->RemoveActiveEnemy(this);
	Destroy(false, true);
}

