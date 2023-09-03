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
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, GetName() + "Disabled");
    bCanAttack = false;
    StopCharge();
    LaserComponent->Deactivate();
    // ToDo: Disable laser effect (when implemented).
}

void ASniperEnemy::EnableSniperEnemy()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, GetName() + "Enabled");
    bCanAttack = true;
    LaserComponent->Activate();
}

void ASniperEnemy::SpecialAttack()
{
}

void ASniperEnemy::StartCharge()
{
    if(bCanAttack)
    {
        bIsCharging = true;
        LaserComponent->Activate();
    }
}

void ASniperEnemy::StopCharge()
{
    bIsCharging = false;
    LaserComponent->Deactivate();
}
