// Created by Spring2022_Capstone team


#include "MantleSystemComponent.h"
#include "PlayerCharacter.h"

UMantleSystemComponent::UMantleSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UMantleSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayersCharacterMovementComponent = Cast<APlayerCharacter>(GetOwner())->GetCharacterMovement();
	
}

void UMantleSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UMantleSystemComponent::Mantle()
{
	
}

///////////////////////////////////////////////////////////////////////////// TIMELINE FUNCTIONS /////////////////////////////////////////////////////////////////////////////
void UMantleSystemComponent::TimelineCallback(float val)
{
}

void UMantleSystemComponent::TimelineFinishedCallback()
{
}

void UMantleSystemComponent::PlayTimeline()
{
}


