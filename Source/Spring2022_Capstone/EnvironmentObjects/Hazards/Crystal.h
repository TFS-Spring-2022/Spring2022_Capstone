// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"
#include "Spring2022_Capstone/GameplaySystems/ScoreSystemManagerSubSystem.h"
#include "Spring2022_Capstone/Sounds/SoundManagerSubSystem.h"
#include "Crystal.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS()
class SPRING2022_CAPSTONE_API ACrystal : public AActor, public IDamageableActor
{
	GENERATED_BODY()
	
public:
	ACrystal();

	virtual void BeginPlay() override;

	UPROPERTY()
	UScoreSystemManagerSubSystem* ScoreManagerSubsystem;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent *CrystalMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent *SphereCollider;
	UPROPERTY(EditDefaultsOnly, Category = "Effect", meta = (AllowPrivateAccess = true))
    UNiagaraSystem*  ExplosionEffectNiagaraSystem;
	UPROPERTY(EditDefaultsOnly, Category = "Effect", meta = (AllowPrivateAccess = true))
	UNiagaraSystem* PulseEffectNiagaraSystem;
	
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
    bool bIsPulsing = false;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
    float Damage;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
    float PulseInterval;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
    float TotalPulses;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	UAudioComponent* PulseSoundAudioComponent;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundCue* PulseSound;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundCue* ExplosionSound;

public:	
	UFUNCTION(BlueprintCallable)
	virtual bool DamageActor(AActor* DamagingActor, const float DamageAmount, FName HitBoneName = "NONE") override;
	UFUNCTION(BlueprintCallable)
	void Pulse();
	UFUNCTION(BlueprintCallable)
	void Explode();

private:
	FTimerHandle PulseTimer;
	int PulseCounter = 0;

	FTimerHandle ExplosionEffectDelayTimerHandle;
	UFUNCTION()
	void PlayDelayedExplosionEffect();
	const float EXPLOSION_EFFECT_DELAY = 0.5f;	// Time(s) before the crystal explosion effect is started.

	bool bExplosionEffectPlayed = false;
};
