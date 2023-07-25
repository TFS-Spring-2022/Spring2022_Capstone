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

	// Temporary for testing
	UPROPERTY(VisibleAnywhere, Category = "Attack System | Debug")
	AActor* TokenHolder; // Testing going to use AActor instead of ABaseEnemy

	UPROPERTY(EditAnywhere, Category = "Attack System | Debug")
	TArray<AActor*> Agents; // Note: Temporarily using AActor* for testing
	// TArray<ABaseEnemy*> Agents;
	
	/// Components
	UPROPERTY(EditAnywhere, Category = "Attack System | Components")
	UCurveFloat* DistanceMultiplierFloatCurve;

	UPROPERTY(EditAnywhere, Category = "Attack System | Components")
	UCurveFloat* AngleDifferenceMultiplierFloatCurve;
	
	float CalculateDelay(AActor* Agent, AActor* Target);

	float CalculateAgentRelevance(AActor* Agent, AActor* Target);

	float GetStanceMultiplier(AActor* Agent); 

	float GetCoverMultiplier(AActor* Agent); 
	
};
