// Created by Spring2022_Capstone team

#include "SniperEnemy.h"
#include "NiagaraComponent.h"
#include "Spring2022_Capstone/Enemies/BaseEnemyProjectile.h"
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
        
        if (APlayerCharacter *Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
        {
            Player->DamageActor(this, Damage);
        }
    }
}

void ASniperEnemy::SpecialAttack()
{
    if(bCanAttack)
    {
        if (!Projectile) { return; }
        if (APlayerCharacter *Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
        {
            FVector vectorToPlayer = Player->GetActorLocation() - GetActorLocation();
            FRotator FacingRotator = vectorToPlayer.Rotation();
            GetWorld()->SpawnActor<ABaseEnemyProjectile>(Projectile, ProjectileSpawnPoint->GetComponentLocation(), FacingRotator);
        }
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
