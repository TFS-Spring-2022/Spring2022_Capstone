// Created by Spring2022_Capstone team

#include "RangedEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "BaseEnemyProjectile.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

void ARangedEnemy::SpecialAttack()
{
    GetWorld()->SpawnActor<ABaseEnemyProjectile>(Projectile, GetActorLocation(), GetActorRotation());
}
