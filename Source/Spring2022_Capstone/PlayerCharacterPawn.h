// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacterPawn.h"
#include "PlayerCharacterPawn.generated.h"

class UInputAction;

UCLASS()
class SPRING2022_CAPSTONE_API APlayerCharacterPawn : public ABaseCharacterPawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction *LookAction;
};
