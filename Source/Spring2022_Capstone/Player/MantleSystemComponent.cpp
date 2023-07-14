// Created by Spring2022_Capstone team


#include "MantleSystemComponent.h"

// Sets default values for this component's properties
UMantleSystemComponent::UMantleSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UMantleSystemComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UMantleSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

