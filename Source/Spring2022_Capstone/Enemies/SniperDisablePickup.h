// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "SniperDisablePickup.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API ASniperDisablePickup : public ATriggerSphere
{
	GENERATED_BODY()

	ASniperDisablePickup();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* PickupStaticMesh;
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	
};
