// Created by Spring2022_Capstone team

#include "BasePickup.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
ABasePickup::ABasePickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::OnOverlapBegin);
}

// Called every frame
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
