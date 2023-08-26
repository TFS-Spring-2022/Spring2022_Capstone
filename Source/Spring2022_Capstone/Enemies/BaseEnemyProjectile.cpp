// Created by Spring2022_Capstone team

#include "BaseEnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseEnemyProjectile::ABaseEnemyProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->MaxSpeed = 300.f;
	ProjectileMovementComponent->InitialSpeed = 300.f;
	ProjectileMovementComponent->ProjectileGravityScale = .0f;

	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->HomingAccelerationMagnitude = 300.f;
}

void ABaseEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();

	APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
	{
		ProjectileMovementComponent->HomingTargetComponent = PlayerPawn->GetRootComponent();
	}
}

// Called every frame
void ABaseEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
