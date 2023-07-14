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

	bCanMantle = false;
	
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

	// Check for blocking surface /////////////////////////////////////////////////////////////
	if(GetWorld()->SweepSingleByChannel(MantleCheckHit, StartLocation, EndLocation, FQuat::Identity,
		ECC_Visibility, FCollisionShape::MakeCapsule(CAPSULE_TRACE_RADIUS, CAPSULE_TRACE_HALF_HEIGHT), TraceParams))
	{

		// I do not understand what counts as a walkable surface.
		if(PlayersCharacterMovementComponent->IsWalkable(MantleCheckHit))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Hit - Walkable Surface");
			bCanMantle = false;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Hit - Not Walkable Surface");
			bCanMantle = true;
			InitialPoint = MantleCheckHit.ImpactPoint;
			InitialNormal = MantleCheckHit.ImpactNormal;
		}
	}

	// Trace downwards for surface target location ///////////////////////////////////////////////////////////////
	FHitResult HitResult2;
	
	FVector SecondStartLocation = FVector(InitialPoint.X, InitialPoint.Y, PlayersCharacterMovementComponent->GetActorLocation().Z - CAPSULE_TRACE_ZAXIS_RAISE); // Subtracting to account for raise in above check
	
	FVector DepthOfSurfaceMantleSeeNote = InitialNormal * -30;

	SecondStartLocation = SecondStartLocation + DepthOfSurfaceMantleSeeNote;
	
	if(GetWorld()->SweepSingleByChannel(HitResult2, FVector(SecondStartLocation.X, SecondStartLocation.Y, SecondStartLocation.Z + 120), SecondStartLocation, FQuat::Identity,
		ECC_Visibility, FCollisionShape::MakeSphere(30), TraceParams))
	{
		// I do not understand what counts as a walkable surface.
		if(PlayersCharacterMovementComponent->IsWalkable(HitResult2))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Dont mantle it");
			bCanMantle = false;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Mantling");
			TargetLocation = HitResult2.Location;
		}
	}
	
}

