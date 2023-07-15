// Created by Spring2022_Capstone team


#include "MantleSystemComponent.h"
#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"

UMantleSystemComponent::UMantleSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UMantleSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacterMovementComponent = Cast<APlayerCharacter>(GetOwner())->GetCharacterMovement();
	PlayerCapsuleComponent = PlayerCharacterMovementComponent->GetCharacterOwner()->GetCapsuleComponent();

	SetTraceParams();
	
}

void UMantleSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UMantleSystemComponent::Mantle()
{

	// Check for blocking wall //
	FHitResult BlockingWallHitResult;
	
	FVector StartLocation =	PlayerCharacterMovementComponent->GetActorLocation();
	StartLocation.Z += CAPSULE_TRACE_ZAXIS_RAISE; // Raise capsule trace to avoid lower surfaces/

	FVector EndLocation = StartLocation + (GetOwner()->GetActorForwardVector() * CAPSULE_TRACE_REACH); 

	if(GetWorld()->SweepSingleByChannel(BlockingWallHitResult, StartLocation, EndLocation, FQuat::Identity, ECC_Visibility,
		FCollisionShape::MakeCapsule(CAPSULE_TRACE_RADIUS, PlayerCapsuleComponent->GetScaledCapsuleHalfHeight()), TraceParams))
	{

		if(!PlayerCharacterMovementComponent->IsWalkable(BlockingWallHitResult))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Climbable Object Hit");

			InitialPoint = BlockingWallHitResult.ImpactPoint;
			InitialNormal = BlockingWallHitResult.ImpactNormal;
		}
		else
		{
			bCanMantle = false; 
			//return; // Leave Mantle() other calculations are unnecessary.
		}
		
	}
}

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


