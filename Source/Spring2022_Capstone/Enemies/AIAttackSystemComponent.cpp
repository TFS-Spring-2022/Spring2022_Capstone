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
	
	TokenTimer = 0;
	TokenPassTime = 9999;

	bHoldingToken = true;
}

void UAIAttackSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(Agents.IsEmpty() )
		return;

	
	
	// Start token timer
	TokenTimer += DeltaTime;
	if(TokenTimer > TokenPassTime)
	{
		if(TokenHolder && bHoldingToken == true)
		{
			Cast<IAttackSystemAgentInterface>(TokenHolder)->ReceiveToken();
			bHoldingToken = false;
		}
		TokenTimer = 0;
	}
	
	for (AActor* ActiveAgent : Agents)
	{
		
		float AgentRelevancy = CalculateAgentRelevance(ActiveAgent, PlayerInstance); 
		
		// Recheck current token holder and replace if more relevant
		if(AgentRelevancy >	 CalculateAgentRelevance(TokenHolder, PlayerInstance))
		{
			TokenHolder = ActiveAgent;
		}
	}

	TokenPassTime = CalculateDelay(TokenHolder, PlayerInstance);
	
}

float UAIAttackSystemComponent::CalculateDelay(AActor* Agent, AActor* Target)
{

	if(!Agent || !Target)
		return 0;

	// Delay = BaseDelay * (DistanceMultiplier * StanceMultiplier * CoverMultiplier * FacingDirectionMultiplier * VelocityMultiplier);
	
	const float DistanceMultiplier = DelayDistanceMultiplierFloatCurve->GetFloatValue(FVector::Dist(Agent->GetActorLocation(), Target->GetActorLocation()));

	const float StanceMultiplier = GetStanceMultiplier(Target);

	const float CoverMultiplier = GetCoverMultiplier(Agent, Target);

	const float FacingDirectionMultiplier = DelayAngleDifferenceMultiplierFloatCurve->GetFloatValue(UKismetMathLibrary::FindLookAtRotation(Target->GetActorLocation(), Agent->GetActorLocation()).Yaw); // We want to hit them in the back less. So we need to get the target's look at rotation because agent should always be looking straight at target.

	const float VelocityMultiplier = GetVelocityMultiplier(Target);
	
	return BaseDelay * (DistanceMultiplier * StanceMultiplier * CoverMultiplier * FacingDirectionMultiplier * VelocityMultiplier) + BaseDelay; // Adding that +BaseDelay to ensure there is always a minimum time between hits.
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

float UAIAttackSystemComponent::GetStanceMultiplier(const AActor* Target) const
{
	
	float StanceMultiplier = 1.0f;
	
	if(Target->IsA(APlayerCharacter::StaticClass()))
	{
		if(PlayerInstance->bIsCrouched)
			StanceMultiplier += .3f;
		if(!PlayerMovementComponent->IsMovingOnGround()) // Target Player Jumping
			StanceMultiplier += .1;
	}
	return StanceMultiplier;
}

float UAIAttackSystemComponent::GetCoverMultiplier(const AActor* Agent, AActor* Target) const
{
	
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(Agent);

	ACharacter* TargetCharacter = Cast<ACharacter>(Target);

	/// Check if player is in half cover ///
	FHitResult HalfCoverCheckHitResult;
	FVector StartHalfCoverCheckTrace = Agent->GetActorLocation();
	FVector EndHalfCoverCheckTrace = TargetCharacter->GetMesh()->GetBoneLocation(LowerBone);

	if(GetWorld()->LineTraceSingleByChannel(HalfCoverCheckHitResult, StartHalfCoverCheckTrace, EndHalfCoverCheckTrace, ECC_Visibility, *TraceParams))
	{
		if(HalfCoverCheckHitResult.BoneName == LowerBone)
			return 0.7; // No half cover
		else
			return 1.5; // Target behind half cover
	}
	return 1;
}

// Calculate weighted sum and the highest score is chosen as relevant agent. 
float UAIAttackSystemComponent::CalculateAgentRelevance(AActor* Agent, AActor* Target)
{
	if(!Agent || !Target)
		return 0;
	
	// AgentRelevanceScore = ArcheType * (DistanceValueMultiplier * TargetExposureMultiplier * Attack Status)
	// ToDo: Agent Attack Status: If the agent is currently under attack, it is more likely it will receive a token.
	// ToDo: Token Assignment History: Agents that have not received a token in a long time may have a higher change of receiving the token soon. 

	// Temporary. ToDo: Add enemy Archetypes to be passed to AIAttackSystemComponent. This will allow some enemies to be more likely to receive the token.
	float ArchetypeValue = 0.5; 
	
	// Distance.
	float DistanceValueMultiplier = RelevanceDistanceMultiplierFloatCurve->GetFloatValue(FVector::Dist(Agent->GetActorLocation(), Target->GetActorLocation()));

	// Target Exposure .
	float TargetExposureMultiplier = GetTargetExposureMultiplier(Agent, Target);

	// Final Calculation
	return ArchetypeValue * ((DistanceValueMultiplier /* 2*/) * TargetExposureMultiplier);
}
	
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

void UAIAttackSystemComponent::RemoveAgent(AActor* AgentToRemove)
{
	if(Agents.Contains(AgentToRemove))
	{
		if(TokenHolder == AgentToRemove)
			TokenHolder = nullptr;

		Agents.Remove(AgentToRemove);

		bHoldingToken = true;
	}
}

void UAIAttackSystemComponent::ClearAgents()
{
	Agents.Empty();
	bHoldingToken = true;
}

void UAIAttackSystemComponent::ReturnToken()
{
	bHoldingToken = true;
}
