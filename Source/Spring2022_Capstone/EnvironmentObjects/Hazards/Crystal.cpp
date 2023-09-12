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

