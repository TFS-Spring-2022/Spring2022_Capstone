// Created by Spring2022_Capstone team

#include "SniperProjectile.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

ASniperProjectile::ASniperProjectile()
{
    SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
    SphereCollider->SetupAttachment(RootComponent);
}

void ASniperProjectile::BeginPlay()
{
    Super::BeginPlay();

    ProjectileMovementComponent->MaxSpeed = 300.f;
	ProjectileMovementComponent->InitialSpeed = 300.f;
	ProjectileMovementComponent->ProjectileGravityScale = .0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

    ProjectileMesh->OnComponentHit.AddDynamic(this, &ASniperProjectile::OnHit);
}

void ASniperProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalizedImpulse, const FHitResult &Hit)
{
    // TODO: Explosive round
    Destroy();
}
