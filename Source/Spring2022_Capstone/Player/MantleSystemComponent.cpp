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
	SetTraceParams();
	
}

void UMantleSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UMantleSystemComponent::Mantle()
{
	
void UMantleSystemComponent::SetTraceParams()
{
	TraceParams.bTraceComplex = true;

	// Ignore Player and all it's components.
	TraceParams.AddIgnoredActor(GetOwner());
	// Warning. Anything that causes Component ownership change or destruction will invalidate array.
	TSet<UActorComponent*> ComponentsToIgnore = GetOwner()->GetComponents(); 
	for (UActorComponent* Component : ComponentsToIgnore)
		TraceParams.AddIgnoredComponent(Cast<UPrimitiveComponent>(Component));
	
	// ToDo: Ensure weapons are ignored.
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


