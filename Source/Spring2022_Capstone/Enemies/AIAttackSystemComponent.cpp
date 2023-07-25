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
	PlayerInstance = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Temp/To: Assign random agent at the start of a wave.
	if(Agents[0])
		TokenHolder = Agents[0];
	
}


// Called every frame
void UAIAttackSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	for (AActor* ActiveAgent : Agents)
	{
		const float AgentRelevancy = CalculateAgentRelevance(ActiveAgent, PlayerInstance);
		
		// Recheck current token holder and replace if more relevant
		if(AgentRelevancy < CalculateAgentRelevance(TokenHolder, PlayerInstance))
			TokenHolder = ActiveAgent;
	}
	
}

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
float UAIAttackSystemComponent::CalculateAgentRelevance(AActor* Agent, AActor* Target)
{
	// Weighted Sum
	float AgentWeightedSum = 0;
	// Distance To Target (This one is getting the furthest actor, how should I reverse this? Lowest weight is most relevant maybe?
	AgentWeightedSum += FVector::Dist(Agent->GetActorLocation(), Target->GetActorLocation());
	
	// Target Exposure
	// Check for foot bones and head bone to see if player in half cover
	// Archetype
	// If Agent is Currently Under Attack
	// Token Is Currently Under Attack

	return AgentWeightedSum;
}
}

