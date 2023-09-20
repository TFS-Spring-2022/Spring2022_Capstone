// Created by Spring2022_Capstone team

#include "Crystal.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ACrystal::ACrystal()
{
	PrimaryActorTick.bCanEverTick = true;

	CrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrystalMesh"));
	RootComponent = CrystalMesh;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);

	PulseSoundAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	PulseSoundAudioComponent->SetupAttachment(RootComponent);
}

void ACrystal::BeginPlay()
{
	Super::BeginPlay();

	Super::BeginPlay();
	ScoreManagerSubsystem = GetGameInstance()->GetSubsystem<UScoreSystemManagerSubSystem>();
}

bool ACrystal::DamageActor(AActor *DamagingActor, const float DamageAmount, FName HitBoneName)
{
	if (bIsPulsing)
	{
		return false;
	}
	GetWorld()->GetTimerManager().SetTimer(ExplosionEffectDelayTimerHandle, this, &ACrystal::PlayDelayedExplosionEffect, EXPLOSION_EFFECT_DELAY, false);
	Pulse();

	PulseSoundAudioComponent->Play();
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
		PulseSoundAudioComponent->Stop();
		PulseCounter = 0;
	}
}

void ACrystal::Explode()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),PulseSound,this->GetActorLocation(),this->GetActorRotation());
	if(bExplosionEffectPlayed)
	{
		if(PulseEffectNiagaraSystem)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), PulseEffectNiagaraSystem, GetActorLocation(), GetActorRotation(), GetActorScale());
		}
	}

	
	
	TArray<AActor *> OverlappingActors;
	SphereCollider->GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if(OverlappingActor->Implements<UDamageableActor>() && !OverlappingActor->IsA(ACrystal::StaticClass()))
		{
			if(Cast<IDamageableActor>(OverlappingActor)->DamageActor(this, Damage))
			{
				if(ScoreManagerSubsystem)
					ScoreManagerSubsystem->IncrementScoreCounter(EScoreCounters::EnemiesKilledWithHazards);
			}
		}
	}
}

void ACrystal::PlayDelayedExplosionEffect()
{
	if(ExplosionEffectNiagaraSystem)
	{
		// Rotate explosion effect towards player.
		const FRotator PlayerLookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffectNiagaraSystem, GetActorLocation(), PlayerLookAtRotation, GetActorScale());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),ExplosionSound,this->GetActorLocation(),this->GetActorRotation());
	}
		
	
	// Spawn first pulse with initial explosion
	if(PulseEffectNiagaraSystem)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), PulseEffectNiagaraSystem, GetActorLocation(), GetActorRotation(), GetActorScale());

	bExplosionEffectPlayed = true;
}
