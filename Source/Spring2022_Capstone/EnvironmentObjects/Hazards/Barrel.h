// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"
#include "Barrel.generated.h"

class USphereComponent;
class UHealthComponent;

UCLASS()
class SPRING2022_CAPSTONE_API ABarrel : public AActor, public IDamageableActor
{
	GENERATED_BODY()
	
public:	
	ABarrel();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent *BarrelMesh;
	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent *SphereCollider;

	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = true))
	UHealthComponent *HealthComp;
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = true))
    float Damage;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual bool DamageActor(AActor* DamagingActor, const float DamageAmount, FName HitBoneName = "NONE") override;
	UFUNCTION(BlueprintCallable)
	void Explode();

};
