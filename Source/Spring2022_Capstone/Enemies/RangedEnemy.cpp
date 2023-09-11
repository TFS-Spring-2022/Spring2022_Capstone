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

void ARangedEnemy::Death()
{
    Super::Death();

    if(SoundManagerSubSystem)
    {
        SoundManagerSubSystem->PlayGruntSoundEvent(SoundManagerSubSystem,VoiceAudioComponent,5);
    }
}
