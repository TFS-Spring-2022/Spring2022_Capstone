// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"
#include "Crystal.generated.h"

class USphereComponent;

UCLASS()
class SPRING2022_CAPSTONE_API ACrystal : public AActor, public IDamageableActor
{
	GENERATED_BODY()
	
public:
	ACrystal();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent *CrystalMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent *SphereCollider;

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
    bool bIsPulsing = false;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
    float Damage;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
    float PulseInterval;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
    float TotalPulses;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual bool DamageActor(AActor* DamagingActor, const float DamageAmount, FName HitBoneName = "NONE") override;
	UFUNCTION(BlueprintCallable)
	void Pulse();

private:
	FTimerHandle PulseTimer;
	int PulseCounter = 0;
};