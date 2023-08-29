// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemyProjectile.generated.h"

class UProjectileMovementComponent;
UCLASS()
class SPRING2022_CAPSTONE_API ABaseEnemyProjectile : public AActor
{
	GENERATED_BODY()

public:
	ABaseEnemyProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent *ProjectileMesh;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent *ProjectileMovementComponent;
	
	UPROPERTY(EditAnywhere, Category = "Sounds")
	UAudioComponent *TrackingSoundComponent;

public:
	virtual void Tick(float DeltaTime) override;
	
};
