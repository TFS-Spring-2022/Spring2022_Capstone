// Created by Spring2022_Capstone team

#include "DamageArea.h"
#include "Components/SphereComponent.h"

ADamageArea::ADamageArea()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);
}

void ADamageArea::BeginPlay()
{
	Super::BeginPlay();
}
