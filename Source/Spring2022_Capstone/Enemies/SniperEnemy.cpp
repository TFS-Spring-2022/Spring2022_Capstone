// Created by Spring2022_Capstone team

#include "SniperEnemy.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

ASniperEnemy::ASniperEnemy()
{
    LaserComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LaserComponent"));
    LaserComponent->SetupAttachment(WeaponMesh);
}

void ASniperEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    {
    if (bIsCharging && LaserComponent->IsActive())
        LaserComponent->SetVectorParameter("Laser_End", UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->GetActorLocation());
    }
}

void ASniperEnemy::Attack()
{
    // TODO: Implementation
    UE_LOG(LogTemp, Display, TEXT("ATTACK"));
}

void ASniperEnemy::SpecialAttack()
{
}

void ASniperEnemy::StartCharge()
{
    bIsCharging = true;
    LaserComponent->Activate();
}

void ASniperEnemy::StopCharge()
{
    bIsCharging = false;
    LaserComponent->Deactivate();
}
