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
    SoundManagerSubSystem->PlayGruntSoundEvent(VoiceAudioComponent,4);
}

void ARangedEnemy::AttackHit()
{
    Super::AttackHit();

    if(!PlayerCharacter->isGrounded)
    {
        if(FMath::RandRange(1,25) == 1)
            SoundManagerSubSystem->PlayGruntSoundEvent(VoiceAudioComponent,0);
    }
}




