// Created by Spring2022_Capstone team

#include "Crystal.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

ACrystal::ACrystal()
{
	PrimaryActorTick.bCanEverTick = true;

	CrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrystalMesh"));
	RootComponent = CrystalMesh;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);

	ExplosionEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ExplosionEffect"));
    ExplosionEffect->SetupAttachment(RootComponent);
	ExplosionEffect->SetActive(false);
	ExplosionEffect->SetAutoActivate(false);
}

bool ACrystal::DamageActor(AActor *DamagingActor, const float DamageAmount, FName HitBoneName)
{
	if (bIsPulsing)
	{
		return false;
	}
	GetWorld()->GetTimerManager().SetTimer(ExplosionEffectDelayTimerHandle, this, &ACrystal::PlayDelayedExplosionEffect, EXPLOSION_EFFECT_DELAY, false);
	Pulse();
	return true;
}

void ACrystal::Pulse()
{
	Explode();
	bIsPulsing = true;
	PulseCounter++;
	if (PulseCounter < TotalPulses)
	{
		GetWorld()->GetTimerManager().SetTimer(PulseTimer, this, &ACrystal::Pulse, PulseInterval);
	}
	else
	{
		bIsPulsing = false;
		PulseCounter = 0;
		if(ExplosionEffect)
			ExplosionEffect->SetActive(false);
	}
}

void ACrystal::Explode()
{
	TArray<AActor *> OverlappingActors;
	SphereCollider->GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if(OverlappingActor->Implements<UDamageableActor>() && !OverlappingActor->IsA(ACrystal::StaticClass()))
		{
			Cast<IDamageableActor>(OverlappingActor)->DamageActor(this, Damage);
		}
	}
}

void ACrystal::PlayDelayedExplosionEffect()
{
	if(ExplosionEffect)
		ExplosionEffect->SetActive(true);
}
