// Created by Spring2022_Capstone team

#include "RangedEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

ARangedEnemy::ARangedEnemy()
{
    
}

void ARangedEnemy::Attack()
{
	// Test Attack, Just here to show Damage Indicator functionality.
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	Player->DamageActor(this, 10.0f);
}

void ARangedEnemy::Reload()
{

}
