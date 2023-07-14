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
	
	Mantle();
}

void UMantleSystemComponent::Mantle()
{
	
	FVector StartLocation = PlayersCharacterMovementComponent->GetActorLocation();
	StartLocation.Z += CAPSULE_TRACE_ZAXIS_RAISE; // Raise capsule slightly to avoid low edges (ToDo: Play with height because will always be airborne)

	FVector EndLocation = PlayersCharacterMovementComponent->GetOwner()->GetActorForwardVector() * CAPSULE_TRACE_DISTANCE;
	EndLocation += StartLocation;

	FCollisionQueryParams TraceParams;
	TraceParams.bTraceComplex = true; 
	TraceParams.AddIgnoredActor(GetOwner());
	
	if(GetWorld()->SweepSingleByChannel(MantleCheckHit, StartLocation, EndLocation, FQuat::Identity,  ECC_Visibility, FCollisionShape::MakeCapsule(CAPSULE_TRACE_RADIUS, CAPSULE_TRACE_HALF_HEIGHT), TraceParams))
	{
		
		if(PlayersCharacterMovementComponent->IsWalkable(MantleCheckHit))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Hit - Walkable Surface");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Hit - Not Walkable Surface");
		}
		
	}
}

