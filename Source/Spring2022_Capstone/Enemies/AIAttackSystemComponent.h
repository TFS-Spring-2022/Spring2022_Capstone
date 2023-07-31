// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "Components/ActorComponent.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "AIAttackSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPRING2022_CAPSTONE_API UAIAttackSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIAttackSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	/// Runtime
	UPROPERTY()
	APlayerCharacter* PlayerInstance;

	UPROPERTY()
	UPawnMovementComponent* PlayerMovementComponent;

	// Temporary holding for testing
	UPROPERTY(VisibleAnywhere, Category = "Attack System | Debug")
	AActor* TokenHolder; // Testing going to use AActor instead of ABaseEnemy

	// AGENTS MUST IMPLEMENT AttackSystemAgentInterface!
	UPROPERTY(EditAnywhere, Category = "Attack System | Debug")
	TArray<AActor*> Agents; // Note: Temporarily using AActor* for testing
	// TArray<ABaseEnemy*> Agents;
	
	/// Components

	// Float Curve used to calculate delay with distance to Target.
	UPROPERTY(EditAnywhere, Category = "Attack System | Components")
	UCurveFloat* DelayDistanceMultiplierFloatCurve;

	// Float Curve used to calculate delay with Agent/Target line of sight.
	UPROPERTY(EditAnywhere, Category = "Attack System | Components")
	UCurveFloat* DelayAngleDifferenceMultiplierFloatCurve;

	// Float Curve used to calculate Agent relevance with distance to target.
	UPROPERTY(EditAnywhere, Category = "Attack System | Components")
	UCurveFloat* RelevanceDistanceMultiplierFloatCurve;

	float CalculateDelay(AActor* Agent, AActor* Target);
	
	/**
	 * @brief Calculates the weighted sum of Agent's relevance, used to assign next holder of attack token.
	 * @param Agent The Agent who's sum is being evaluated.
	 * @param Target The Target the Agent is in combat with.
	 * @return Weighted sum of the Agent's relevance, calculated through distance, target exposure, archetype, and combat status.
	 */
	float CalculateAgentRelevance(AActor* Agent, AActor* Target);

	// Returns a value based on the target's cover status (full cover, half cover, open).
	float GetTargetExposureMultiplier(AActor* Agent, AActor* Target);

	float GetVelocityMultiplier(const AActor* Target) const;

	// Bone used to check if lower half of target's body is behind cover Note - ToDo: Change when player skeleton added, currently using Unreal Engine 'pelvis'.
	UPROPERTY(EditAnywhere, Category = "Attack System | Bones")
	FName LowerBone;

	// Bone used to check if upper half of target's body is behind cover Note - ToDo: Change when player skeleton added, currently using Unreal Engine 'spine_03'.
	UPROPERTY(EditAnywhere, Category = "Attack System | Bones")
	FName UpperBone;

	// Debug - Testing values ToDo: Erase
	UPROPERTY(VisibleAnywhere, Category = "Attack System | Debug")
	float Agent1RelevanceValue;

	UPROPERTY(VisibleAnywhere, Category = "Attack System | Debug")
	float Agent2RelevanceValue;

	UPROPERTY(VisibleAnywhere, Category = "Attack System | Debug")
	float Agent3RelevanceValue;

	UPROPERTY(VisibleAnywhere, Category = "Attack System | Debug")
	float Agent4RelevanceValue;

public:

	/**
	 * @brief Adds the given Agent to the 'Agents' array.
	 */
	void AddNewAgent(AActor* NewAgent); // ToDo: Change parameter type if we change from AActor* to ABaseEnemy*.

	/**
	 * @brief Clears the 'Agents' array of all references.
	 */
	void ClearAgents();

	// Note - When created grapple/dash would be around 1000-1200. Number will need to be changed if movement speed/dash force is updated.
	float const DASH_GRAPPLE_VELOCITY_LENGTH = 1000.0f; // Velocity length when the player is dashing or grappling. 
	
};
