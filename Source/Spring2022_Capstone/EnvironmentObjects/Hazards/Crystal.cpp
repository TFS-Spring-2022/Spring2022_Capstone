// Created by Spring2022_Capstone team

#include "Crystal.h"
#include "Components/SphereComponent.h"

ACrystal::ACrystal()
{
	PrimaryActorTick.bCanEverTick = true;

	CrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrystalMesh"));
	RootComponent = CrystalMesh;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);
}

void ACrystal::BeginPlay()
{
	Super::BeginPlay();
}

void ACrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ACrystal::DamageActor(AActor *DamagingActor, const float DamageAmount, FName HitBoneName)
{
	if (bIsPulsing)
	{
		return false;
	}

	Pulse();
	return true;
}

void ACrystal::Pulse()
{
	// Pulse

	bIsPulsing = true;
	PulseCounter ++;

	UE_LOG(LogTemp, Display, TEXT("Pulse %d"), PulseCounter);

	if (PulseCounter < TotalPulses) {
		GetWorld()->GetTimerManager().SetTimer(PulseTimer, this, &ACrystal::Pulse, PulseInterval);
	} else {
		bIsPulsing = false;
		PulseCounter = 0;
	}
}
