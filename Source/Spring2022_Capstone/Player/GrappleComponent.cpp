// Created by Spring2022_Capstone team

#include "GrappleComponent.h"
#include "GrappleCable.h"

// Sets default values for this component's properties
UGrappleComponent::UGrappleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrappleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrappleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrappleComponent::Fire(FVector TargetLocation)
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, FString::Printf(TEXT("%f %f %f"), TargetLocation.X, TargetLocation.Y, TargetLocation.Z));
}
