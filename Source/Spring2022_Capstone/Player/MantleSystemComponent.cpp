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
	
	FVector BlockingWallCheckStartLocation =	PlayerCharacterMovementComponent->GetActorLocation();
	BlockingWallCheckStartLocation.Z += CAPSULE_TRACE_ZAXIS_RAISE; // Raise capsule trace to avoid lower surfaces/

	FVector BlockingWallCheckEndLocation = BlockingWallCheckStartLocation + (GetOwner()->GetActorForwardVector() * CAPSULE_TRACE_REACH); 

	if(GetWorld()->SweepSingleByChannel(BlockingWallHitResult, BlockingWallCheckStartLocation, BlockingWallCheckEndLocation, FQuat::Identity, ECC_Visibility,
		FCollisionShape::MakeCapsule(CAPSULE_TRACE_RADIUS, PlayerCapsuleComponent->GetScaledCapsuleHalfHeight()), TraceParams))
	{

		if(!PlayerCharacterMovementComponent->IsWalkable(BlockingWallHitResult))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Climbable Object Hit");

			InitialPoint = BlockingWallHitResult.ImpactPoint;
			InitialNormal = BlockingWallHitResult.ImpactNormal;
		}
		else
		{
			bCanMantle = false; 
			//return; // Leave Mantle() other calculations are unnecessary.
		}
	}

	// Trace downwards for surface //
	FHitResult SurfaceCheckHitResult;

	FVector SurfaceCheckStartLocation = FVector(InitialPoint.X, InitialPoint.Y, PlayerCharacterMovementComponent->GetActorLocation().Z - CAPSULE_TRACE_ZAXIS_RAISE) + InitialNormal * MANTLE_SURFACE_DEPTH; // Subtracting to account for raise above
	SurfaceCheckStartLocation.Z += 120; // Surface height check ToDo: Get player/capsule height and use that

	FVector SurfaceCheckEndLocation = FVector(InitialPoint.X, InitialPoint.Y, PlayerCharacterMovementComponent->GetActorLocation().Z - CAPSULE_TRACE_ZAXIS_RAISE) + InitialNormal * MANTLE_SURFACE_DEPTH; // Subtracting to account for raise above
	
	if(GetWorld()->SweepSingleByChannel(SurfaceCheckHitResult, SurfaceCheckStartLocation, SurfaceCheckEndLocation, FQuat::Identity, ECC_Visibility,
		FCollisionShape::MakeSphere(CAPSULE_TRACE_RADIUS), TraceParams))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Surface Object Hit"); // Im confused what exactly are we looking for here. No hits I would think

		DrawDebugSphere(GetWorld(), SurfaceCheckStartLocation, CAPSULE_TRACE_RADIUS, 8, FColor::Red, false, 5.0f);
		DrawDebugSphere(GetWorld(), SurfaceCheckEndLocation, CAPSULE_TRACE_RADIUS, 8, FColor::Blue, false, 5.0f);
		
		if(SurfaceCheckHitResult.bBlockingHit && PlayerCharacterMovementComponent->IsWalkable(SurfaceCheckHitResult))
		{
			// Can mantle
			TargetLoc = SurfaceCheckHitResult.Location;
		}
		else
		{
			// Cannot mantle
			bCanMantle = false; 
			TargetLocation = FVector(0, 0, 0); // Why do we have this right now?
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
	// BIsClimbing = false;
}



void UMantleSystemComponent::PlayTimeline()
{
}


