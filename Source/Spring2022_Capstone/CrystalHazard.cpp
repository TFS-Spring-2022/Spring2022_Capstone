// Created by Spring2022_Capstone team


#include "CrystalHazard.h"
#include "GameplaySystems/DamageableActor.h"

// Sets default values
ACrystalHazard::ACrystalHazard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACrystalHazard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrystalHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrystalHazard::DamageActor(AActor* DamagingActor, const float DamageAmount)
{

	IDamageableActor::DamageActor(DamagingActor, DamageAmount);
	DamageActorBP();

}