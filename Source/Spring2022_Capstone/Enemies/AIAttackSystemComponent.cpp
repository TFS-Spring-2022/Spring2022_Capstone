// Created by Spring2022_Capstone team


#include "AIAttackSystemComponent.h"

// Sets default values for this component's properties
UAIAttackSystemComponent::UAIAttackSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIAttackSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIAttackSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
float UAIAttackSystemComponent::CalculateDelay(AActor* Agent, AActor* Target)
{

	// Delay = BaseDelay * (DistanceMultiplayer * StanceMultiplier * CoverMultiplier * FacingDirectionMultiplier * VelocityMultiplier);  

	const float BaseDelay = 0.5; // Question - Per Character?
	const float DistanceMultiplier = DistanceMultiplierFloatCurve->GetFloatValue(FVector::Dist(Agent->GetActorLocation(), Target->GetActorLocation()));
	const float StanceMultiplier = GetStanceMultiplier(Agent);
	const float CoverMultiplier = GetCoverMultiplier(Agent);
	const float FacingDirectionMultiplier = AngleDifferenceMultiplierFloatCurve->GetFloatValue(UKismetMathLibrary::FindLookAtRotation(Agent->GetActorLocation(), Target->GetActorLocation()).Yaw);
	const float VelocityMultiplier = 2; // Question - How should I calculate this?

	const float Delay = BaseDelay * (DistanceMultiplier * StanceMultiplier * FacingDirectionMultiplier * CoverMultiplier * FacingDirectionMultiplier * VelocityMultiplier);

	// ...
}

