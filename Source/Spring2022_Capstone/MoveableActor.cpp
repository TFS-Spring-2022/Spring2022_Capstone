// Created by Spring2022_Capstone team


#include "MoveableActor.h"
#include "Components/TimelineComponent.h"

// Sets default values
AMoveableActor::AMoveableActor()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Initialize default values
	RestTimeBetweenMovements = 2.0f;
	MovementSpeed = 500.0f;
	CurrentRestTime = 0.0f;
	CurrentPointIndex = 0;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	Platform->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMoveableActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Save the initial location of the actor
	InitialLocation = GetActorLocation();
}

// Called every frame
void AMoveableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if there are movement points defined
	if (MovementPoints.Num() == 0)
		return;

	// Calculate the movement direction and distance
	FVector CurrentTargetPoint = MovementPoints[CurrentPointIndex];
	FVector Direction = CurrentTargetPoint - GetActorLocation();
	float DistanceToTarget = Direction.Size();

	// Move the actor towards the target point
	if (DistanceToTarget > 10.0f)
	{
		Direction.Normalize();
		FVector NewLocation = GetActorLocation() + Direction * MovementSpeed * DeltaTime;
		SetActorLocation(NewLocation);
	}
	else
	{
		// If the actor reached the target point, rest for a while
		CurrentRestTime += DeltaTime;
		if (CurrentRestTime >= RestTimeBetweenMovements)
		{
			// Move to the next point and reset rest time
			CurrentPointIndex = (CurrentPointIndex + 1) % MovementPoints.Num();
			CurrentRestTime = 0.0f;
		}
	}
}