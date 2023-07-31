// Created by Spring2022_Capstone team

#include "RangedEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

ARangedEnemy::ARangedEnemy()
{
    
}

void ARangedEnemy::AttackHit()
{
	// Test AttackHit, Just here to show Damage Indicator functionality.
	// APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	// Player->DamageActor(this, 10.0f);

	// ToDo: GetPlayerLocation
	// ToDo: Raycast towards play (Need FHitResults to play particle effects.
		// Raycast needs a range. (Unsure where to store this, maybe a const in BaseEnemy)

	// ToDo: Random chance to move Raycast and miss player
}

void ARangedEnemy::Reload()
{
	// ToDo: Stop player from moving/attacking while they reload
}
