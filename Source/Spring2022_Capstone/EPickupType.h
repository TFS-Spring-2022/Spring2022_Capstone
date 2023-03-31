// Created by Spring2022_Capstone team

#pragma once

#include "EPickupType.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum EPickupType
{
    HealthPickupSmall UMETA(DisplayName = "HealthPickupSmall"),
    HealthPickupMedium UMETA(DisplayName = "HealthPickupMedium"),
    HealthPickupLarge UMETA(DisplayName = "HealthPickupLarge"),
};