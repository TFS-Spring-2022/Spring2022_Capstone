// Created by Spring2022_Capstone team

#include "BaseEnemy.h"
#include "Spring2022_Capstone/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

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
	}
}
