// Created by Spring2022_Capstone team

#include "GrappleComponent.h"
#include "GrappleHook.h"
#include "CableComponent.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CableActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

UGrappleComponent::UGrappleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrappleComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGrappleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GrappleState == EGrappleState::Firing && FMath::Abs(FVector::Dist(GetStartLocation(), _GrappleHook->GetActorLocation())) > GrappleRange)
	{
		CancelGrapple(false);
	}
	else if (GrappleState == EGrappleState::Attached)
	{
		if (APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(GetOwner()))
		{
			UCharacterMovementComponent *MovementComponent = PlayerCharacter->GetCharacterMovement();
			FVector ToGrappleHookDirection = GetToGrappleHookDirection();
			MovementComponent->AddForce(ToGrappleHookDirection * 10000);
			if (FVector::Distance(_GrappleHook->GetActorLocation(), GetOwner()->GetActorLocation()) < 250 ||
				FVector::DotProduct(InitialHookDirection2D, FVector(ToGrappleHookDirection.X, ToGrappleHookDirection.Y, 0)) < 0)
			{
				CancelGrapple();
			}
		}
	}
}

void UGrappleComponent::Fire(FVector TargetLocation)
{
	OnGrappleActivatedDelegate.ExecuteIfBound();
	GrappleState = EGrappleState::Firing;

	FVector StartLocation = GetStartLocation();
	FVector VectorDirection = (TargetLocation - StartLocation);
	VectorDirection.Normalize();

	// Spawn and attach grapple

	FActorSpawnParameters SpawnInfo;
	FTransform ActorTransform = FTransform(StartLocation);
	_GrappleHook = GetWorld()->SpawnActorDeferred<AGrappleHook>(GrappleHookType, ActorTransform);
	_GrappleHook->FireVelocity = VectorDirection * FireSpeed;
	_GrappleHook->OnActorHit.AddDynamic(this, &UGrappleComponent::OnHit);
	_GrappleHook->SphereCollider->SetCollisionProfileName(TEXT("OverlapAll"));
	UGameplayStatics::FinishSpawningActor(_GrappleHook, ActorTransform);

	// Spawn and attach cable

	Cable = GetWorld()->SpawnActor<ACableActor>(ACableActor::StaticClass(), StartLocation, UKismetMathLibrary::MakeRotFromX(VectorDirection));
	Cable->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
	Cable->CableComponent->EndLocation = FVector::ZeroVector;
	Cable->CableComponent->SetAttachEndTo(_GrappleHook, TEXT(""));
	Cable->CableComponent->CableWidth = 1.25f;
	Cable->CableComponent->bEnableStiffness = false;
	Cable->CableComponent->SubstepTime = 0.005f;
	Cable->CableComponent->SetCollisionProfileName(TEXT("OverlapAll"));
}

FVector UGrappleComponent::GetStartLocation()
{
	FVector TransformedDirection = UKismetMathLibrary::TransformDirection(GetOwner()->GetActorTransform(), GrappleOffset);
	FVector StartingLocation = TransformedDirection + GetOwner()->GetActorLocation();
	return StartingLocation;
}

void UGrappleComponent::DecrementGrappleCooldown(float Seconds)
{
	Cooldown -= Seconds;

	if(Cooldown <= MinimumGrappleCooldown)
		Cooldown = MinimumGrappleCooldown;
}

void UGrappleComponent::OnHit(AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse, const FHitResult &Hit)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		return;
	}

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UGrappleComponent::MaxGrappleTimeReached, MaximumGrappleTime, false);

	GrappleState = EGrappleState::Attached;

	if (APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(GetOwner()))
	{
		UCharacterMovementComponent *MovementComponent = PlayerCharacter->GetCharacterMovement();
		FVector ToGrappleHookDirection = GetToGrappleHookDirection();
		MovementComponent->GroundFriction = 0;
		MovementComponent->GravityScale = 0;
		MovementComponent->AirControl = 0.2;
		MovementComponent->Velocity = ToGrappleHookDirection * GrappleForce;
		InitialHookDirection2D = FVector(ToGrappleHookDirection.X, ToGrappleHookDirection.Y, 0);
		InitialHookDirection2D.Normalize();
	}
}

void UGrappleComponent::MaxGrappleTimeReached()
{
	CancelGrapple();
}

void UGrappleComponent::CancelGrapple(bool ShouldTriggerCooldown)
{
	if (_GrappleHook && Cable)
	{
		_GrappleHook->Destroy();
		_GrappleHook = nullptr;

		Cable->Destroy();
		Cable = nullptr;

		if (ShouldTriggerCooldown)
		{
			if (APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(GetOwner()))
			{
				UCharacterMovementComponent *MovementComponent = PlayerCharacter->GetCharacterMovement();
				MovementComponent->GroundFriction = 1;
				MovementComponent->GravityScale = 1;
				MovementComponent->AirControl = 0.05;
			}
			GrappleState = EGrappleState::Cooldown;
			GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UGrappleComponent::ResetStatus, Cooldown, false);
			OnGrappleCooldownStartDelegate.ExecuteIfBound(CooldownTimerHandle);
		} else {
			ResetStatus();
		}
	}
}

FVector UGrappleComponent::GetToGrappleHookDirection()
{
	FVector Direction = _GrappleHook->GetActorLocation() - GetOwner()->GetActorLocation();
	Direction.Normalize();
	return Direction;
}

void UGrappleComponent::ResetStatus()
{
	GrappleState = EGrappleState::ReadyToFire;
	CooldownTimerHandle.Invalidate();
	OnGrappleCooldownEndDelegate.ExecuteIfBound();
}
