// Created by Spring2022_Capstone team


#include "AIAttackSystemComponent.h"

#include "AttackSystemAgentInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UAIAttackSystemComponent::UAIAttackSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UAIAttackSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerInstance = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(PlayerInstance)
		PlayerMovementComponent = PlayerInstance->GetMovementComponent();

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
		if(AgentRelevancy >	 CalculateAgentRelevance(TokenHolder, PlayerInstance))
		{
			TokenHolder = ActiveAgent;
		}
		
	}

	// testing
	GetVelocityMultiplier(PlayerInstance);

	/* Debug Printing 
	Agent1RelevanceValue = CalculateAgentRelevance(Agents[0], PlayerInstance);
	Agent2RelevanceValue = CalculateAgentRelevance(Agents[1], PlayerInstance);
	Agent3RelevanceValue = CalculateAgentRelevance(Agents[2], PlayerInstance);
	Agent4RelevanceValue = CalculateAgentRelevance(Agents[3], PlayerInstance);
	*/
}

float UAIAttackSystemComponent::CalculateDelay(AActor* Agent, AActor* Target)
{

	// Delay = BaseDelay * (DistanceMultiplier * StanceMultiplier * CoverMultiplier * FacingDirectionMultiplier * VelocityMultiplier);

	const float BaseDelay = 0.5; // Question - Where should I set this? Per player of just a base one? Either works really. I like the total one because it allows us to set a universal feel for attacking enemies.

	const float DistanceMultiplier = DelayDistanceMultiplierFloatCurve->GetFloatValue(FVector::Dist(Agent->GetActorLocation(), Target->GetActorLocation()));

	const float StanceMultiplier = 1; // ToDo: Get if PlayerCharacter is Airborne/Crouched/Standing

	const float CoverMultiplier = 1; // I should probably do something like if in half cover then make this 1.5 or 2 to make it longer

	const float FacingDirectionMultiplier = DelayAngleDifferenceMultiplierFloatCurve->GetFloatValue(UKismetMathLibrary::FindLookAtRotation(Target->GetActorLocation(), Agent->GetActorLocation()).Yaw); // We want to hit them in the back less. So we need to get the target's look at rotation because agent should always be looking straight at target.

	const float VelocityMultiplier = GetVelocityMultiplier(Target);

	const float Delay = BaseDelay * (DistanceMultiplier, StanceMultiplier, CoverMultiplier, FacingDirectionMultiplier, VelocityMultiplier);
	
	return Delay;
}

float UAIAttackSystemComponent::GetVelocityMultiplier(const AActor* Target) const
{
																
	const float TargetVelocityLength = Target->GetVelocity().Length(); 

	// Target Still
	if(TargetVelocityLength == 0)
		return 0;
		
	if(Target->IsA(APlayerCharacter::StaticClass()))
	{
		if(PlayerMovementComponent->IsMovingOnGround())
		{
			if(PlayerInstance->GetIsSprinting() == true) // Target Sprinting
			{
				return 1.8;
			}
			if(TargetVelocityLength == PlayerInstance->GetMovementComponent()->GetMaxSpeed()) // Target Walking
			{
				return 1.5f;
			}
		}
		else if(TargetVelocityLength >= DASH_GRAPPLE_VELOCITY_LENGTH) // Target Dashing/Grappling/Falling
		{
			return 2.2;
		}
	}
	return 1;
}


// Calculate weighted sum and the highest score is chosen as relevant agent. 
float UAIAttackSystemComponent::CalculateAgentRelevance(AActor* Agent, AActor* Target)
{

	// AgentRelevanceScore = ArcheType * (DistanceValueMultiplier * TargetExposureMultiplier * Attack Status)
	
	// ToDo: 
	// When selecting the most relevant agent we are going to look at:
	// ____________________________________________________________ //
	// Distance to the Target: Close the agent the more options it has to receive a token.
	// Target Exposure: The more access to player (player outside of half/full cover) the higher chance of obtaining a token.
	// Archetype: The tougher the type of enemy, the easier it is to get a token.
	// Agent Attack Status: If the agent is currently under attack, it is more likely it will receive a token.
	// (Currently avoiding) Token Assignment History: Agents that have not received a token in a long time may have a higher change of receiving the token soon. 

	// Temporary. ToDo: Add enemy Archetypes to be passed to AIAttackSystemComponent. This will allow some enemies to be more likely to receive the token.
	float ArchetypeValue = 0.5; 
	
	// Distance.
	float DistanceValueMultiplier = RelevanceDistanceMultiplierFloatCurve->GetFloatValue(FVector::Dist(Agent->GetActorLocation(), Target->GetActorLocation()));

	// Target Exposure .
	float TargetExposureMultiplier = GetTargetExposureMultiplier(Agent, Target);

	// Final Calculation
	float AgentRelevance = ArchetypeValue * ((DistanceValueMultiplier /* 2*/) * TargetExposureMultiplier);
	
	return AgentRelevance;
	
}

// ToDo: Rename GetTargetExposure
float UAIAttackSystemComponent::GetTargetExposureMultiplier(AActor* Agent, AActor* Target)
{

	float CoverValue = 1;

	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(Agent);

	ACharacter* TargetCharacter = Cast<ACharacter>(Target);
	
	/// Check if player is in full cover ///
	FHitResult FullCoverCheckHitResult;
	FVector StartFullCoverCheckTrace = Agent->GetActorLocation();
	FVector EndFullCoverCheckTrace = TargetCharacter->GetMesh()->GetBoneLocation(UpperBone);

	if(GetWorld()->LineTraceSingleByChannel(FullCoverCheckHitResult, StartFullCoverCheckTrace, EndFullCoverCheckTrace, ECC_Visibility, *TraceParams))
	{
		if(FullCoverCheckHitResult.BoneName == UpperBone)
			CoverValue += .5f; // Target's upper half is hittable.
		else
			CoverValue -= .5f; // Target's upper half is behind cover.			
	}
	
	/// Check if player is in half cover ///
	FHitResult HalfCoverCheckHitResult;
	FVector StartHalfCoverCheckTrace = Agent->GetActorLocation();
	FVector EndHalfCoverCheckTrace = TargetCharacter->GetMesh()->GetBoneLocation(LowerBone);

	if(GetWorld()->LineTraceSingleByChannel(HalfCoverCheckHitResult, StartHalfCoverCheckTrace, EndHalfCoverCheckTrace, ECC_Visibility, *TraceParams))
	{
		if(HalfCoverCheckHitResult.BoneName == LowerBone)
			CoverValue += .5f; // Target's lower half is hittable
		else
			CoverValue -= .5f; // Target's upper half is behind cover
	}
	
	return CoverValue;
}

void UAIAttackSystemComponent::AddNewAgent(AActor* NewAgent)
{
	// If the given AActor is a valid Agent and does not exist inside Agents array, add NewAgent.
	if(NewAgent->Implements<UAttackSystemAgentInterface>())
	{
		if(!Agents.Contains(NewAgent))
			Agents.Add(NewAgent);	
	}
}

void UAIAttackSystemComponent::ClearAgents()
{
	Agents.Empty();
}
