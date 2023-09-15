// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"
#include "Spring2022_Capstone/Sounds/SoundManagerSubSystem.h"
#include "Barrel.generated.h"

class USphereComponent;
class UHealthComponent;
class ADamageArea;
class UNiagaraComponent;

UCLASS()
class SPRING2022_CAPSTONE_API ABarrel : public AActor, public IDamageableActor
{
	GENERATED_BODY()

public:
	ABarrel();

	UFUNCTION(BlueprintCallable)
	virtual bool DamageActor(AActor *DamagingActor, const float DamageAmount, FName HitBoneName = "NONE") override;
	UFUNCTION(BlueprintCallable)
	void Explode();
	UFUNCTION(BlueprintCallable)
	void SpawnDamageArea();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent *BarrelMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent *SphereCollider;
	UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
    TSubclassOf<ADamageArea> DamageArea;
	UPROPERTY(EditDefaultsOnly, Category = "Effect", meta = (AllowPrivateAccess = true))
    UNiagaraComponent*  ExplosionNiagaraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	UHealthComponent *HealthComp;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Damage;
};
