// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "SniperEnemy.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.h"
#include "SniperEnemyHit.generated.h"


UCLASS()
class SPRING2022_CAPSTONE_API ASniperEnemyHit : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ASniperEnemyHit();
	float WarningAreaEditable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Explode();


	UPROPERTY(VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* HitMesh;

};