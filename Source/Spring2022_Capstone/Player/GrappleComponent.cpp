// Created by Spring2022_Capstone team

#include "GrappleComponent.h"
#include "GrappleHook.h"
#include "CableComponent.h"
#include "PlayerCharacter.h"
#include "CableActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

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
void UGrappleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GrappleState == EGrappleState::Firing && FMath::Abs(FVector::Dist(GetStartLocation(),_GrappleHook->GetActorLocation())) > GrappleRange)
	{
		CancelGrapple();
	}
	// ...
}

void UGrappleComponent::Fire(FVector TargetLocation)
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, FString::Printf(TEXT("%f %f %f"), TargetLocation.X, TargetLocation.Y, TargetLocation.Z));
	GrappleState = EGrappleState::Firing;

	FVector StartLocation = GetStartLocation();
	FVector VectorDirection = (TargetLocation - StartLocation);
	VectorDirection.Normalize();

	// Spawn and attach grapple

	FActorSpawnParameters SpawnInfo;
	FTransform ActorTransform = FTransform(StartLocation);
	_GrappleHook = GetWorld()->SpawnActorDeferred<AGrappleHook>(GrappleHookType, ActorTransform);
	_GrappleHook->FireVelocity = VectorDirection * FireSpeed;
	_GrappleHook->SphereCollider->OnComponentHit.AddDynamic(this, &UGrappleComponent::OnHit);
	_GrappleHook->SphereCollider->SetCollisionProfileName(TEXT("OverlapAll"));
	UGameplayStatics::FinishSpawningActor(_GrappleHook, ActorTransform);

	// Spawn and attach cable

	Cable = GetWorld()->SpawnActor<ACableActor>(ACableActor::StaticClass(), StartLocation, UKismetMathLibrary::MakeRotFromX(VectorDirection));
	Cable->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
	Cable->CableComponent->EndLocation = FVector::ZeroVector;
	Cable->CableComponent->SetAttachEndTo(_GrappleHook, TEXT(""));
	Cable->CableComponent->CableWidth = 1.25f;
	Cable->CableComponent->bEnableStiffness = true;
	Cable->CableComponent->SubstepTime = 0.005f;
	Cable->CableComponent->SetCollisionProfileName(TEXT("OverlapAll"));

	// FTimerHandle handle;
	// GetWorld()->GetTimerManager().SetTimer(handle, this, &UGrappleComponent::CancelGrapple, GrappleTimer, false);
}

FVector UGrappleComponent::GetStartLocation()
{
	FVector TransformedDirection = UKismetMathLibrary::TransformDirection(GetOwner()->GetActorTransform(), GrappleOffset);
	FVector StartingLocation = TransformedDirection + GetOwner()->GetActorLocation();
	return StartingLocation;
}

void UGrappleComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		return;
	}

	GrappleState = EGrappleState::Attached;
}

void UGrappleComponent::CancelGrapple()
{
	if (_GrappleHook && Cable)
	{
		_GrappleHook->Destroy();
		_GrappleHook = nullptr;

		Cable->Destroy();
		Cable = nullptr;

		GrappleState = EGrappleState::Cooldown;
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UGrappleComponent::ResetStatus, Cooldown, false);
	}
}

void UGrappleComponent::ResetStatus()
{
	GrappleState = EGrappleState::ReadyToFire;
}
