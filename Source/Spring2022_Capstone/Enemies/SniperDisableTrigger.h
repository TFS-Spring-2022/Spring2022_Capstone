// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "SniperEnemy.h"
#include "Engine/TriggerSphere.h"
#include "SniperDisableTrigger.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API ASniperDisableTrigger : public ATriggerSphere
{
	GENERATED_BODY()

	ASniperDisableTrigger();

	UPROPERTY(EditAnywhere, Category = "Linked Sniper")
	ASniperEnemy* SniperToDisable;
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	
};
