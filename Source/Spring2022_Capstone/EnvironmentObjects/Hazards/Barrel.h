// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barrel.generated.h"

class USphereComponent;

UCLASS()
class SPRING2022_CAPSTONE_API ABarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	ABarrel();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent *BarrelMesh;
	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent *SphereCollider;

public:	
	virtual void Tick(float DeltaTime) override;

};
