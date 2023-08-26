// Created by Spring2022_Capstone team


#include "BaseEnemyProjectile.h"

// Sets default values
ABaseEnemyProjectile::ABaseEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

