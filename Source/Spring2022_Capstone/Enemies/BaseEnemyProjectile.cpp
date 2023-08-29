// Created by Spring2022_Capstone team

#include "BaseEnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABaseEnemyProjectile::ABaseEnemyProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

void ABaseEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
