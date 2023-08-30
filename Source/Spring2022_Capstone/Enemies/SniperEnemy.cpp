// Created by Spring2022_Capstone team

#include "SniperEnemy.h"
#include "NiagaraComponent.h"

ASniperEnemy::ASniperEnemy()
{
    LaserComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LaserComponent"));
	LaserComponent->SetupAttachment(WeaponMesh);
}

void ASniperEnemy::Attack()
{
    //TODO: Implementation
    UE_LOG(LogTemp, Display, TEXT("ATTACK"));
}

void ASniperEnemy::SpecialAttack()
{
    
}

void ASniperEnemy::StartCharge()
{
    
}

void ASniperEnemy::StopCharge()
{

}
