// Created by Spring2022_Capstone team

#include "BaseEnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

ABaseEnemyProjectile::ABaseEnemyProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	TrackingSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Tracking audio Comp"));
	
}

void ABaseEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	TrackingSoundComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TrackingSoundComponent->Play();
}

// Called every frame
void ABaseEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
