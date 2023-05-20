#pragma once

#include "GrappleState.generated.h"

UENUM(BlueprintType)
enum EGrappleState
{
	ReadyToFire 	UMETA(DisplayName = "ReadyToFire"),
	Firing 			UMETA(DisplayName = "Firing"),
	Cooldown 		UMETA(DisplayName = "Cooldown"),
};