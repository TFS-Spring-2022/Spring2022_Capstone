// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GrappleState.h"
#include "Components/ActorComponent.h"
#include "GrappleComponent.generated.h"

class AGrappleCable;
class AGrappleHook;
class ACableActor;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPRING2022_CAPSTONE_API UGrappleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrappleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Grapple")
	float Cooldown = 1.f;

	UPROPERTY(EditAnywhere, Category = "Grapple")
	FVector GrappleOffset;
	UPROPERTY(EditAnywhere, Category = "Grapple")
	float FireSpeed = 5000;

	UPROPERTY(EditAnywhere, Category = "Grapple")
	TSubclassOf<AGrappleHook> GrappleHookType;

	UPROPERTY(EditAnywhere, Category = "Grapple")
	AGrappleHook *_GrappleHook = nullptr;
	UPROPERTY(EditAnywhere, Category = "Grapple")
	ACableActor *Cable = nullptr;

	FVector InitialHookDirection2D;
	FVector GetToGrappleHookDirection();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Grapple")
	TEnumAsByte<EGrappleState> GrappleState;
	UPROPERTY(EditAnywhere, Category = "Grapple")
	float GrappleRange = 500.f;

	UFUNCTION()    
    void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit );
	UFUNCTION()
	void CancelGrapple();
	UFUNCTION()
	void ResetStatus();

	void Fire(FVector TargetLocation);
	FVector GetStartLocation();
};
