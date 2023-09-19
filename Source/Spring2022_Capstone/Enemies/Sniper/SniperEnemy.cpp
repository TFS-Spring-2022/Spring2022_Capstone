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

void ASniperEnemy::BeginPlay()
{
    Super::BeginPlay();
    SoundManagerSubSystem = GetGameInstance()->GetSubsystem<USoundManagerSubSystem>();
    LaserComponent->SetAutoActivate(false);

    EnableSniperEnemy();
}

void ASniperEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
        
    
    if(bIsCharging)
    {
        LaserComponent->SetVectorParameter("Laser_End", UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->GetActorLocation());
        chargeTime += DeltaTime;
        LaserComponent->SetFloatParameter("Laser_Width", chargeTime);
        if(chargeTime >= 5.f)
            LockOn();
    }

    
}

void ASniperEnemy::LockOn()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "LockedOn");
    bIsCharging = false;
    GetWorld()->GetTimerManager().SetTimer(TimeBeforeShotTimerHandler, this, &ASniperEnemy::Attack, 1.5f, false);
}

void ASniperEnemy::Attack()
{
    if(bCanAttack)
    {
        if(PlayerCharacter->GetHasSniperDisableObject())
            SoundManagerSubSystem->PlaySniperSoundEvent(VoiceAudioComponent,5);

        LaserComponent->Deactivate();
        //Shoots to see if the player is hit
        
        FHitResult HitResult;
        FVector StartTrace = this->GetActorLocation();
        StartTrace.Z -= 10; // TEMP: Offset to make debug draw lines visible without moving.
        FVector ForwardVector = this->GetActorForwardVector();
        FVector EndTrace = ((ForwardVector * Range) + StartTrace);
        FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
        TraceParams->AddIgnoredComponent(this->GetMesh());

        if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
        {
            if (Cast<APlayerCharacter>(HitResult.GetActor()))
            {
                Cast<APlayerCharacter>(HitResult.GetActor())->DamageActor(this, Damage);
            }
        }
        Reload();
    }
}

void ASniperEnemy::Reload()
{
    StopCharge();
    GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandler, this, &ASniperEnemy::StartCharge, 5.f, false);
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
            if(SoundManagerSubSystem)
                SoundManagerSubSystem->PlaySniperSoundEvent(VoiceAudioComponent,0);
            if(Projectile)
                GetWorld()->SpawnActor<ABaseEnemyProjectile>(Projectile, ProjectileSpawnPoint->GetComponentLocation(), FacingRotator);
        }
    }
}

void ASniperEnemy::DisableSniperEnemy()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, GetName() + "Disabled");
    bCanAttack = false;
    if(SoundManagerSubSystem)
        SoundManagerSubSystem->PlaySniperSoundEvent(VoiceAudioComponent,6);
    StopCharge();
    
    // ToDo: Disable laser effect (when implemented).
}

void ASniperEnemy::EnableSniperEnemy()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, GetName() + "Enabled");
    bCanAttack = true;
    bIsCharging = true;
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
    chargeTime = 0;
    LaserComponent->SetActive(false);
}





