// Created by Spring2022_Capstone team


#include "ExplosiveBarrel.h"
#include "GameplaySystems/DamageableActor.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosiveBarrel::DamageActor(AActor* DamagingActor, const float DamageAmount)
{

	IDamageableActor::DamageActor(DamagingActor, DamageAmount);
	DamageActorBP();
	
}