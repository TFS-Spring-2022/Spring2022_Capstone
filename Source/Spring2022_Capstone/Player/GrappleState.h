#pragma once

#include "GrappleState.generated.h"

UENUM(BlueprintType)
enum EGrappleState
{
	ReadyToFire 	UMETA(DisplayName = "ReadyToFire"),
	Firing 			UMETA(DisplayName = "Firing"),
	Attached 		UMETA(DisplayName = "Attached"),
	Cooldown 		UMETA(DisplayName = "Cooldown"),
};