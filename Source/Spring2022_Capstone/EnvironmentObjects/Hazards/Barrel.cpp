// Created by Spring2022_Capstone team

#include "Barrel.h"
#include "Components/SphereComponent.h"


ABarrel::ABarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = BarrelMesh;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);

}

void ABarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

