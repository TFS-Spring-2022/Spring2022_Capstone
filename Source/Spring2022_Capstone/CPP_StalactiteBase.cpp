// Created by Spring2022_Capstone team

#include "Components/StaticMeshComponent.h"
#include "CPP_StalactiteBase.h"

// Sets default values
ACPP_StalactiteBase::ACPP_StalactiteBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StalactiteMesh"));

	if (RootSceneComponent == nullptr) return;
	if (MeshComponent == nullptr) return;

	MeshComponent->SetupAttachment(RootSceneComponent);

	

}

// Called when the game starts or when spawned
void ACPP_StalactiteBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_StalactiteBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

