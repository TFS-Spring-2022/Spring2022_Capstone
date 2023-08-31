// Created by Spring2022_Capstone team


#include "SniperEnemy.h"

void ASniperEnemy::Attack()
{
    if(bCanAttack)
    {
        //TODO: Implementation
        UE_LOG(LogTemp, Display, TEXT("ATTACK"));
    }
}

void ASniperEnemy::BeginPlay()
{
    Super::BeginPlay();

    EnableSniperEnemy();
}

void ASniperEnemy::DisableSniperEnemy()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, GetName() + "Sniper Enemy Disabled");
    bCanAttack = false;
    // ToDo: Disable laser effect (when implemented).
}

void ASniperEnemy::EnableSniperEnemy()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, GetName() + "Sniper Enemy Enabled");
    bCanAttack = true;
    // ToDo: Enable laser effect (when implemented).
}
