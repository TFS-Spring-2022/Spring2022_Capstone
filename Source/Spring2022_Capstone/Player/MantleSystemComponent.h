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
	UCharacterMovementComponent* PlayerCharacterMovementComponent;

	UPROPERTY()
	UCapsuleComponent* PlayerCapsuleComponent;
	
// Runtime
	
	
	const float CAPSULE_TRACE_ZAXIS_RAISE = 45.0f;
	const float CAPSULE_TRACE_REACH = 45.0f; // Distance to wall to mantle ** Note - Needs Tinkering
	
	
	const float CAPSULE_TRACE_RADIUS = 30.0f;
	const float CAPSULE_TRACE_HALF_HEIGHT = 60.0f;

	const float MANTLE_SURFACE_DEPTH = -60.0f; //-30.0f; // Depth the player will climb up to. // This is not true iunno what this even does D:
	const float MANTLE_SPACE_CHECK_HEIGHT_BUFFER = 15.0f; // Amount space check sphere cast is raised to ensure not inside mantle object.

	const float MANTLE_SPACE_CHECK_RADIUS = 10.0f; // Radius of sphere cast used when checking if player can mantle into crouched space. Must be smaller then character capsule radius.
	
public:
	void Mantle();

private:

// Runtime
	
	bool bCanMantle;
	
	FVector InitialPoint; // Initial point of contact on blocking wall check.
	FVector InitialNormal; // Initial normal of contact on blocking wall check.

	FVector TargetLocation;

	FVector TargetLoc; // Why does he have two what is the deal with that? I think I can remove the TargetLocation later it seems to be perma 0 in his version

	FVector InitialPlayerPosition; // Player's position before mantle begins. Used to calculate movement through mantle lerp.
	
// Timeline Members
	UPROPERTY()
	FTimeline MantleTimeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* MantleTimelineFloatCurve;
	
	// This function is called when the timeline finishes playing.
	UFUNCTION()
	void TimelineFinishedCallback();
	
	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;
	
	void SetTraceParams();

	FCollisionQueryParams TraceParams;

	bool CheckMantleSpace(FVector LocationToCheck);

	UPROPERTY(EditAnywhere, Category = "Mantle | Components")
	TSubclassOf<UCameraShakeBase> ClimbingCameraShake;

	UPROPERTY(EditAnywhere)
	bool bIsMantleing;

	UPROPERTY(EditAnywhere, Category = "Mantle | Components")
	ACharacter* Player; // Doesn't need APlayerCharacter* Can throw circular dependency error
	
	
};
