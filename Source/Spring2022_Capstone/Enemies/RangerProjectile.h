// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyProjectile.h"
#include "RangerProjectile.generated.h"

/**
 *
 */
UCLASS()
class SPRING2022_CAPSTONE_API ARangerProjectile : public ABaseEnemyProjectile
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalizedImpulse, const FHitResult &Hit);
};
