// Created by Spring2022_Capstone team


#include "MantleSystemComponent.h"
#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UMantleSystemComponent::UMantleSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMantleSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(GetOwner());
	PlayerCharacterMovementComponent = Player->GetCharacterMovement();
	PlayerCapsuleComponent = Player->GetCapsuleComponent();

	SetTraceParams();

	// Setup Timeline
	FOnTimelineFloat TimelineCallback;
	FOnTimelineEventStatic TimelineFinishedCallback;

	// Length of Timeline is set from of MantleTimelineCurve; Length should match duration of CameraShake.
	if(MantleTimelineFloatCurve)
	{
		TimelineFinishedCallback.BindUFunction(this, FName(TEXT("TimelineFinishedCallback")));
		MantleTimeline.AddInterpFloat(MantleTimelineFloatCurve, TimelineCallback); 
		MantleTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
}

void UMantleSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Advance Timeline (Does not play timeline)
	MantleTimeline.TickTimeline(DeltaTime); 
	
	if(bCanMantle && !MantleTimeline.IsPlaying())
	{
		MantleTimeline.PlayFromStart();
		UGameplayStatics::GetPlayerCameraManager(GetWorld(),0)->StartCameraShake(ClimbingCameraShake);
	}
	
	if(MantleTimeline.IsPlaying())
		Player->SetActorLocation(FMath::Lerp(InitialPlayerPosition, TargetLocation, MantleTimeline.GetPlaybackPosition()));
	
}

bool UMantleSystemComponent::AttemptMantle()
{
	if(!CheckForBlockingWall())
		return false;

	if(!TraceDownForMantleSurface())
		return false;

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Reached");
	// Start Mantle (Movement handled in TickComponent().
	PlayerCharacterMovementComponent->SetMovementMode(MOVE_None); // Stop player from moving while mantle-ing.
	
	TargetLocation.Z += MANTLE_VERTICAL_KNOCK;
	InitialPlayerPosition = Player->GetActorLocation();
	bCanMantle = true;
	return true;
}

bool UMantleSystemComponent::CheckForBlockingWall()
{
	FHitResult BlockingWallHitResult;
	
	FVector BlockingWallCheckStartLocation = PlayerCharacterMovementComponent->GetActorLocation();
	BlockingWallCheckStartLocation.Z += CAPSULE_TRACE_ZAXIS_RAISE; // Raise capsule trace to avoid lower surfaces.

	FVector BlockingWallCheckEndLocation = BlockingWallCheckStartLocation + (GetOwner()->GetActorForwardVector() * CAPSULE_TRACE_REACH); 

	if(GetWorld()->SweepSingleByChannel(BlockingWallHitResult, BlockingWallCheckStartLocation, BlockingWallCheckEndLocation, FQuat::Identity, ECC_Visibility,
		FCollisionShape::MakeCapsule(CAPSULE_TRACE_RADIUS, PlayerCapsuleComponent->GetScaledCapsuleHalfHeight()), TraceParams))
	{

		if(!PlayerCharacterMovementComponent->IsWalkable(BlockingWallHitResult))
		{
			// Climbable Object Hit
			InitialPoint = BlockingWallHitResult.ImpactPoint;
			InitialNormal = BlockingWallHitResult.ImpactNormal;
		}
	}
	else
	{
		// Didnt hit a wall.
		bCanMantle = false; 
		return false; 
	}

	return true;
}

bool UMantleSystemComponent::TraceDownForMantleSurface()
{
	FHitResult SurfaceCheckHitResult;

	FVector SurfaceCheckStartLocation = FVector(InitialPoint.X, InitialPoint.Y, PlayerCharacterMovementComponent->GetActorLocation().Z - CAPSULE_TRACE_ZAXIS_RAISE) + InitialNormal * MANTLE_SURFACE_DEPTH; // Subtracting to account for raise above.
	SurfaceCheckStartLocation.Z += PlayerCapsuleComponent->GetScaledCapsuleHalfHeight() * 2;
	
	FVector SurfaceCheckEndLocation = FVector(InitialPoint.X, InitialPoint.Y, PlayerCharacterMovementComponent->GetActorLocation().Z - CAPSULE_TRACE_ZAXIS_RAISE) + InitialNormal * MANTLE_SURFACE_DEPTH; // Subtracting to account for raise above.
	
	if(GetWorld()->SweepSingleByChannel(SurfaceCheckHitResult, SurfaceCheckStartLocation, SurfaceCheckEndLocation, FQuat::Identity, ECC_Visibility,
		FCollisionShape::MakeSphere(CAPSULE_TRACE_RADIUS), TraceParams))
	{

		if(SurfaceCheckHitResult.bBlockingHit && PlayerCharacterMovementComponent->IsWalkable(SurfaceCheckHitResult))
		{ 
			// Can climb up here.
			TargetLocation = SurfaceCheckHitResult.Location;
		}
		else
		{
			// Cannot mantle. // This gets called when there is a hit but it is not a walkable surface.
			bCanMantle = false; 
			TargetLocation = FVector(0, 0, 0); 
			return false;
		}
	}
	else
	{
		// Object to tall.
		bCanMantle = false; 
		TargetLocation = FVector(0, 0, 0); 
		return false;
	}

	return true;
}

void UMantleSystemComponent::SetTraceParams()
{
	TraceParams.bTraceComplex = true;

	// Ignore Player and all it's components.
	TraceParams.AddIgnoredActor(GetOwner());
	// Warning - Anything that causes Component ownership change or destruction will invalidate array so beware when iterating.
	TSet<UActorComponent*> ComponentsToIgnore = GetOwner()->GetComponents(); 
	for (UActorComponent* Component : ComponentsToIgnore)
		TraceParams.AddIgnoredComponent(Cast<UPrimitiveComponent>(Component));
	
	// ToDo: Ensure weapons are ignored when meshes added
}

void UMantleSystemComponent::TimelineFinishedCallback()
{
	PlayerCharacterMovementComponent->SetMovementMode(MOVE_Walking);
	MantleTimeline.Stop();
	bCanMantle = false;
	Cast<APlayerCharacter>(Player)->SetIsMantleing(false);
}
