// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageableActor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UDamageableActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPRING2022_CAPSTONE_API IDamageableActor
{
	GENERATED_BODY()

public:
	/**
	 * @brief 
	 * @param DamagingActor Actor sending damage to implementing class.
	 * @param DamageAmount  Damage value of calling actor.
	 */
	virtual void DamageActor(AActor* DamagingActor, const float DamageAmount, FName HitBoneName = "NONE") {}

};
