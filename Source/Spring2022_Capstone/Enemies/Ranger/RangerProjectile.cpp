// Created by Spring2022_Capstone team

#include "RangerProjectile.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void ARangerProjectile::BeginPlay()
{
    Super::BeginPlay();

    ProjectileMovementComponent->MaxSpeed = 300.f;
	ProjectileMovementComponent->InitialSpeed = 300.f;
	ProjectileMovementComponent->ProjectileGravityScale = .0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->HomingAccelerationMagnitude = 300.f;

    
    
    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (PlayerPawn)
    {
        ProjectileMovementComponent->HomingTargetComponent = PlayerPawn->GetRootComponent();
    }

    ProjectileMesh->OnComponentHit.AddDynamic(this, &ARangerProjectile::OnHit);
}

void ARangerProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalizedImpulse, const FHitResult &Hit)
{
    if (OtherActor->Implements<UDamageableActor>() && OtherActor->IsA(APlayerCharacter::StaticClass())) // Question: Do we want them to be able to do damage to other enemies?
        Cast<APlayerCharacter>(OtherActor)->DamageActor(this, Damage);

    TrackingSoundComponent->SetSound(ExplodingSound);
    if(ExplodingSound)
    {
        SoundManagerSubSystem->PlaySound(OtherActor->GetActorLocation(), ExplodingSound);
    }
    Destroy();
}
