// Created by Spring2022_Capstone team

#include "DamageArea.h"
#include "Components/SphereComponent.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"

ADamageArea::ADamageArea()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);
}

void ADamageArea::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle DurationTimerHandle;
	FTimerHandle DamageTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DurationTimerHandle, this, &ADamageArea::DestroyArea, Duration, false);
	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &ADamageArea::DamageActors, DamageInterval, true);
}

void ADamageArea::DamageActors()
{
	TArray<AActor *> OverlappingActors;
	SphereCollider->GetOverlappingActors(OverlappingActors);

	for (AActor *OverlappingActor : OverlappingActors)
	{
		if (IDamageableActor *DamageableActor = Cast<IDamageableActor>(OverlappingActor))
			DamageableActor->DamageActor(this, Damage);
	}
}

void ADamageArea::DestroyArea()
{
	Destroy();
}
