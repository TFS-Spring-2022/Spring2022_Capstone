// Created by Spring2022_Capstone team

#include "RangedEnemy.h"
#include "RangedWeapon.h"

ARangedEnemy::ARangedEnemy()
{
    Weapon = CreateDefaultSubobject<URangedWeapon>(TEXT("Weapon"));
    Weapon->SetupAttachment(RootComponent);
}
