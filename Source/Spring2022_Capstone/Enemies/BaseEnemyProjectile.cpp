// Created by Spring2022_Capstone team

#include "BaseEnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABaseEnemyProjectile::ABaseEnemyProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;
	ProjectileMovementComponent->ProjectileGravityScale = .0f;
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
