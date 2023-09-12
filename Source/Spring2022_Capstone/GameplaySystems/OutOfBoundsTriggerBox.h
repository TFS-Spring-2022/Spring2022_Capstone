// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "OutOfBoundsTriggerBox.generated.h"

/**
 * Trigger zone to send the player back to PlayerStart if they overlap box.
 * If an enemy overlaps they will be dealt 9999 damage.
 */
UCLASS()
class SPRING2022_CAPSTONE_API AOutOfBoundsTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:

	AOutOfBoundsTriggerBox();

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	
};
