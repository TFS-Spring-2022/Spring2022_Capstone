// Created by Spring2022_Capstone team

#include "Barrel.h"
#include "Components/SphereComponent.h"
#include "Spring2022_Capstone/HealthComponent.h"
#include "Spring2022_Capstone/Enemies/Sniper/SniperEnemy.h"

ABarrel::ABarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	RootComponent = BarrelMesh;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

bool ABarrel::DamageActor(AActor *DamagingActor, const float DamageAmount, FName HitBoneName)
{
	IDamageableActor::DamageActor(DamagingActor, DamageAmount, HitBoneName);
	if (HealthComp)
	{
		if (HealthComp->GetHealth() > 0)
		{
			HealthComp->SetHealth(HealthComp->GetHealth() - DamageAmount);
			if (HealthComp->GetHealth() <= 0)
				Explode();
		}
		return true;
	}
	return false;
}

void ABarrel::Explode()
{
	TArray<AActor *> OverlappingActors;
	SphereCollider->GetOverlappingActors(OverlappingActors);

	for (AActor *OverlappingActor : OverlappingActors)
	{
		if (IDamageableActor *DamageableActor = Cast<IDamageableActor>(OverlappingActor))
		{
			if (DamageableActor == this)
			{
				continue;
			}
			DamageableActor->DamageActor(this, Damage);
		}
	}
	Destroy();
}

void ABarrel::SpawnDamageArea()
{
	if (!DamageArea)
		return;

	GetWorld()->SpawnActor<ABaseEnemyProjectile>(DamageArea, GetActorLocation(), GetActorRotation());
}
