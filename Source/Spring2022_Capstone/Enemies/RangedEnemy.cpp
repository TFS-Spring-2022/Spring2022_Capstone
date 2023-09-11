// Created by Spring2022_Capstone team

#include "RangedEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "BaseEnemyProjectile.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

void ARangedEnemy::SpecialAttack()
{
    if (!Projectile) { return; }
    GetWorld()->SpawnActor<ABaseEnemyProjectile>(Projectile, ProjectileSpawnPoint->GetComponentLocation(), GetActorRotation());
}

void ARangedEnemy::BeginPlay()
{
    Super::BeginPlay();
    if(SoundManagerSubSystem)
    SoundManagerSubSystem->PlayGruntSoundEvent(SoundManagerSubSystem,VoiceAudioComponent,4);
}

void ARangedEnemy::AttackHit()
{
    Super::AttackHit();

    if(!PlayerCharacter->isGrounded)
    {
        SoundManagerSubSystem->PlayGruntSoundEvent(SoundManagerSubSystem,VoiceAudioComponent,0);
    }
}

void ARangedEnemy::Death()
{
    Super::Death();

    if(SoundManagerSubSystem)
    {
        SoundManagerSubSystem->PlayGruntSoundEvent(SoundManagerSubSystem,VoiceAudioComponent,5);
    }
}

bool ARangedEnemy::DamageActor(AActor* DamagingActor, const float DamageAmount, FName HitBoneName)
{
    SoundManagerSubSystem->PlayGruntSoundEvent(SoundManagerSubSystem,VoiceAudioComponent,2);
    return Super::DamageActor(DamagingActor, DamageAmount, HitBoneName);
    
}



