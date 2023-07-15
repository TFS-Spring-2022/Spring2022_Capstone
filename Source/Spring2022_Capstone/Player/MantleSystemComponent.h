// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MantleSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPRING2022_CAPSTONE_API UMantleSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMantleSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	UPROPERTY()
	UCharacterMovementComponent* PlayersCharacterMovementComponent;
	
// Runtime
	const float CAPSULE_TRACE_RADIUS = 30.0f;
	const float CAPSULE_TRACE_HALF_HEIGHT = 60.0f;
	const float CAPSULE_TRACE_DISTANCE = 30.0f;
	const float CAPSULE_TRACE_ZAXIS_RAISE = 45.0f;

public:
	void Mantle();
	
// Timeline Members
	UPROPERTY()
	FTimeline MantleTimeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* MantleTimelineFloatCurve;

	void PlayTimeline();
	
	// This function is called for every tick in the timeline.
	UFUNCTION()
	void TimelineCallback(float val);

	// This function is called when the timeline finishes playing.
	UFUNCTION()
	void TimelineFinishedCallback();
	
	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

private:
	void SetTraceParams();

	FCollisionQueryParams TraceParams;
	
};
