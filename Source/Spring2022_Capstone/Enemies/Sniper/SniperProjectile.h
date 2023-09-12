// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Spring2022_Capstone/Enemies/BaseEnemyProjectile.h"
#include "SniperProjectile.generated.h"

class USphereComponent;

UCLASS()
class SPRING2022_CAPSTONE_API ASniperProjectile : public ABaseEnemyProjectile
{
	GENERATED_BODY()
    
public:
    ASniperProjectile();
	
protected:
	virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
    USphereComponent *SphereCollider;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalizedImpulse, const FHitResult &Hit);
};
