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
	// Sets default values for this actor's properties
	ABaseEnemyProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent *ProjectileMesh;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent *ProjectileMovementComponent;

};
