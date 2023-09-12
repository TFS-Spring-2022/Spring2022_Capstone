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

	// Attempt to start the mantle process
	bool AttemptMantle(); // ToDo: Rename? AttemptMantle()?

private:
	
	UPROPERTY()
	UCharacterMovementComponent* PlayerCharacterMovementComponent;

	UPROPERTY()
	UCapsuleComponent* PlayerCapsuleComponent;

	UPROPERTY()
	ACharacter* Player;

	UPROPERTY(EditAnywhere, Category = "AttemptMantle")
	TSubclassOf<UCameraShakeBase> ClimbingCameraShake;
	
/// Runtime ///
	bool bCanMantle;
	
	FVector InitialPoint; // Initial point of contact on blocking wall check.
	FVector InitialNormal; // Initial normal of contact on blocking wall check.

	FVector InitialPlayerPosition; // Player's position as mantle begins. Used to calculate movement in mantle lerp.
	FVector TargetLocation; // The location the player will be moved to when mantle-ing.

/// Timeline ///
	UPROPERTY()
	FTimeline MantleTimeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* MantleTimelineFloatCurve;
	
	// This function is called when the timeline finishes playing.
	UFUNCTION()
	void TimelineFinishedCallback();
	
/// AttemptMantle Process ///
	
	/**
	 * @brief Capsule cast in front of player to check if object is mantle-able.
	 * @return true - wall is mantle-able
	 */
	bool CheckForBlockingWall();

	/**
	 * @brief Sphere cast above mantle-able object to see if player can get on top.
	 * @return true - can climb onto, false - object is to tall.
	 */
	bool TraceDownForMantleSurface();

	/**
	 * @brief Line trace above Actor to ensure they are not under a platform and going to mantle
	 * through the surface.
	 * @return true - Player is blocked from above and cannot mantle.
	 */
	bool CheckForBlockingAbove() const;

	/**
	* @brief Set CollisionQuereyParams properties of TraceParams
	*/
	void SetTraceParams();
	
	// FCollisionQuereyParams used in all mantle process casts.
	FCollisionQueryParams TraceParams;
	
/// Const Variables ///
	const float CAPSULE_TRACE_ZAXIS_RAISE = 10.0f;		// Amount blocking wall cast is raised to ensure lower surfaces are not caught.
	const float CAPSULE_TRACE_REACH = 45.0f;			// Distance to wall to mantle.
	const float CAPSULE_HEIGHT_BUFFER = 3.0f;			// Additional height added to blocking wall capsule trace.
	const float CAPSULE_TRACE_RADIUS = 30.0f;			// Radius used in check for blocking wall and mantle surface.
	const float MANTLE_SURFACE_DEPTH = -75.0f;			// Depth the player will climb up to. 
	const float MANTLE_VERTICAL_KNOCK = 350.0f;			// Used in mantle process to knock-up the player and ensure they don't get stuck on ground.
	const float BLOCKING_ABOVE_TRACE_DISTANCE = 175.0f;	// Distance traced above the player when searching for an above blocking platform.
	
};
