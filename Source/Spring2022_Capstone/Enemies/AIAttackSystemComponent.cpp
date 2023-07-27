// Created by Spring2022_Capstone team


#include "AIAttackSystemComponent.h"

#include "Kismet/GameplayStatics.h"

UAIAttackSystemComponent::UAIAttackSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UAIAttackSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerInstance = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Temp/ToDo: Assign random agent at the start of a wave.
	if(Agents[0])
		TokenHolder = Agents[0];
	
}

void UAIAttackSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	for (AActor* ActiveAgent : Agents)
	{
		
		float AgentRelevancy = CalculateAgentRelevance(ActiveAgent, PlayerInstance); // removed const to test something
		
		// Recheck current token holder and replace if more relevant
		if(AgentRelevancy < CalculateAgentRelevance(TokenHolder, PlayerInstance))
		{
			TokenHolder = ActiveAgent;
		}
		
	}
}

// Calculate weighted sum and the highest score is chosen as relevant agent. 
float UAIAttackSystemComponent::CalculateAgentRelevance(AActor* Agent, AActor* Target)
{

	// ToDo: 
	// When selecting the most relevant agent we are going to look at:
	// ____________________________________________________________ //
	// Distance to the Target: Close the agent the more options it has to receive a token.
	// Target Exposure: The more access to player (player outside of half/full cover) the higher chance of obtaining a token.
	// Archetype: The tougher the type of enemy, the easier it is to get a token.
	// Agent Attack Status: If the agent is currently under attack, it is more likely it will receive a token.
	// (Currently avoiding) Token Assignment History: Agents that have not received a token in a long time may have a higher change of receiving the token soon. 

	// Distance to target multiplier
	float DistanceValueMultiplier = DistanceMultiplierFloatCurve->GetFloatValue(FVector::Dist(Agent->GetActorLocation(), Target->GetActorLocation()));

	// Temporary for testing
	return DistanceValueMultiplier;
	
	
	// Question/ToDo: How should the calculation look?
	// AgentRelevanceScore = ArcheType * (DistanceValueMultiplier * TargetExposureMultiplier * Attack Status)
}
