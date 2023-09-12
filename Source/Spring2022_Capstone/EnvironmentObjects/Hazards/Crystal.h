// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Crystal.generated.h"

class USphereComponent;

UCLASS()
class SPRING2022_CAPSTONE_API ACrystal : public AActor
{
	GENERATED_BODY()
	
public:
	ACrystal();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent *CrystalMesh;
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent *SphereCollider;

	UPROPERTY(VisibleAnywhere, Category = "Stats", meta = (AllowPrivateAccess = true))
    float Damage;
	UPROPERTY(VisibleAnywhere, Category = "Stats", meta = (AllowPrivateAccess = true))
    float TimeInterval;
	UPROPERTY(VisibleAnywhere, Category = "Stats", meta = (AllowPrivateAccess = true))
    float TotalPulses;

public:	
	virtual void Tick(float DeltaTime) override;

};
