// Created by Spring2022_Capstone team


#include "DevTargets.h"

// Sets default values
ADevTargets::ADevTargets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Comp");
	
	RootComponent = TargetStaticMesh;
	
}

// Called when the game starts or when spawned
void ADevTargets::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADevTargets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADevTargets::ToggleMaterial()
{
	TargetStaticMesh->SetMaterial(0, HitMaterial);
}

