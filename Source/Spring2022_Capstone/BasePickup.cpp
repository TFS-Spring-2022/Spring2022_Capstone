// Created by Spring2022_Capstone team

#include "BasePickup.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "Components/SphereComponent.h"

ABasePickup::ABasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);
}

void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::OnOverlapBegin);
}

void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePickup::OnOverlapBegin(UPrimitiveComponent *Comp, AActor *otherActor, UPrimitiveComponent *otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	APlayerCharacter *player = Cast<APlayerCharacter>(otherActor);
	if (!player)
	{
		return;
	}

	switch (PickupType)
	{
	case EPickupType::HealthPickupSmall:
		player->HealByPercentage(30);
		break;
	case EPickupType::HealthPickupMedium:
		player->HealByPercentage(60);
		break;
	case EPickupType::HealthPickupLarge:
		player->HealByPercentage(100);
		break;
	default:
		break;
	}

	Destroy();
}
