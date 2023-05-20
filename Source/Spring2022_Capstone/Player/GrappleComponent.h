// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GrappleState.h"
#include "Components/ActorComponent.h"
#include "GrappleComponent.generated.h"

class AGrappleCable;

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
	float GRappleTimer = 0.25f;
	UPROPERTY(EditAnywhere, Category = "Grapple")
	TEnumAsByte<EGrappleState> GrappleState;

	UPROPERTY(EditAnywhere, Category = "Grapple")
	AGrappleCable *Cable = nullptr;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void Fire(FVector TargetLocation);
	FVector GetStartLocation();
};
