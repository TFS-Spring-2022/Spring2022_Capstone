// Created by Spring2022_Capstone team

#include "RangerProjectile.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

void ARangerProjectile::BeginPlay()
{
    Super::BeginPlay();
    ProjectileMesh->OnComponentHit.AddDynamic(this, &ARangerProjectile::OnHit);
}

void ARangerProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalizedImpulse, const FHitResult &Hit)
{
    if (OtherActor->Implements<UDamageableActor>() && OtherActor->IsA(APlayerCharacter::StaticClass())) // Question: Do we want them to be able to do damage to other enemies?
        Cast<APlayerCharacter>(OtherActor)->DamageActor(this, Damage);
    Destroy();
}
