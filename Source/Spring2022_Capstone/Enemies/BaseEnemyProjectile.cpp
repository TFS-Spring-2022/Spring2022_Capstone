// Created by Spring2022_Capstone team

#include "BaseEnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
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
	
	//Sounds
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	SoundManagerSubSystem = GameInstance->GetSubsystem<USoundManagerSubSystem>();
	
	TrackingSoundComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	if(TrackingSoundComponent->GetSound())
	{
		TrackingSoundComponent->Play();
	}
}

// Called every frame
void ABaseEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
