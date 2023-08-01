// Created by Spring2022_Capstone team

#include "BaseEnemy.h"
#include "Spring2022_Capstone/HealthComponent.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
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
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, FString::Printf(TEXT("Enemy is taking damage")));

	if (HealthComp)
	{
		HealthComp->SetHealth(HealthComp->GetHealth() - DamageAmount);
<<<<<<< Updated upstream
		if(HealthComp->GetHealth() <= 0)
			Death();
=======

		if (HealthComp->GetHealth() <= 0.0f)
		{
			APlayerCharacter* PlayerRef = Cast<APlayerCharacter>(DamagingActor);

			if(PlayerRef)
				PlayerRef->IncrementKills();

			//Checking to see if health is less than or equal to zero. if it is call increment kills function from player 
			//as this denotes that the enemy is dead.
		}
>>>>>>> Stashed changes
	}
}

void ABaseEnemy::Death()
{
	// ToDo: Rag doll enemy once new skeleton is implemented.
	// Remove enemy from the wave manager (RemoveActiveEnemy() will only remove enemies inside ActiveEnemies[] in the Wave Manager). 
	UEnemyWaveManagementSystem* WaveManager = Cast<ASpring2022_CapstoneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetWaveManager();
	if(WaveManager)
		WaveManager->RemoveActiveEnemy(this);
	Destroy(false, true);
}

