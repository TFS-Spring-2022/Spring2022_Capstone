// Created by Spring2022_Capstone team


#include "Enemies/SniperEnemyHit.h"

#include "DamageableActor.h"
#include "PlayerCharacter.h"
#include "HealthComponent.h"

// Sets default values
ASniperEnemyHit::ASniperEnemyHit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WarningAreaEditable = 5;
	Hitmesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HitMesh"));
	GetWorld()->GetTimeManager().SetTimer(ReloadTimeRanged, this, Explode(), ReloadTime);
	staticMesh->SetWorldScale3D(FVector(WarningAreaEditable, WarningAreaEditable, WarningAreaEditable));
	staticMesh->SetRelativeScale3D(FVector(WarningAreaEditable, WarningAreaEditable, WarningAreaEditable));
}

// Called when the game starts or when spawned
void ASniperEnemyHit::BeginPlay()
{
	Super::BeginPlay();



}

// Called every frame

void Explode()
{

}
}

