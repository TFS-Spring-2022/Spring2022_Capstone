// Created by Spring2022_Capstone team


#include "EnemySpawnPoint.h"

// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComp->SetEnableGravity(false);
	StaticMeshComp->SetGenerateOverlapEvents(false);
	StaticMeshComp->SetVisibility(true);
	StaticMeshComp->SetHiddenInGame(true);
	StaticMeshComp->SetReceivesDecals(false);
	
}

// Called when the game starts or when spawned
void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

