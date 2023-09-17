// Created by Spring2022_Capstone team


#include "SoundManagerSubSystem.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

USoundManagerSubSystem::USoundManagerSubSystem()
{
    
    static ConstructorHelpers::FObjectFinder<USoundCue>WaveStartSoundLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/GameMechanics/SC_WaveStart.SC_WaveStart'"));
    if (WaveStartSoundLoaded.Succeeded())
        WaveStartSound = WaveStartSoundLoaded.Object;

    
#pragma region Player Voice Lines
    
    //Player voice lines SoundCues
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerDeathSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerDeath.SC_PlayerDeath'"));
    if (PlayerDeathSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerDeathSC = PlayerDeathSCLoaded.Object);

    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerDoubleJumpLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_DoubleJump.SC_DoubleJump'"));
    if (PlayerDeathSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerDoubleJumpSC = PlayerDoubleJumpLoaded.Object);
    
    
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerGrapplingSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerGrappling.SC_PlayerGrappling'"));
    if (PlayerGrapplingSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerGrapplingSC = PlayerGrapplingSCLoaded.Object);
    
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerHurtSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerHurt.SC_PlayerHurt'"));
    if (PlayerHurtSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerHurtSC = PlayerHurtSCLoaded.Object);
    
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerHeavyHurSCtLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerHeavyHurt.SC_PlayerHeavyHurt'"));
    if (PlayerHeavyHurSCtLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerHeavyHurtSC = PlayerHeavyHurSCtLoaded.Object);
    
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerSniperSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerSniperHit.SC_PlayerSniperHit'"));
    if (PlayerSniperSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerSniperHitSC = PlayerSniperSCLoaded.Object);
    
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerAFKSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerAFK.SC_PlayerAFK'"));
    if (PlayerAFKSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerAFKSC = PlayerAFKSCLoaded.Object);
    
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerWaveStartSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerWaveStart.SC_PlayerWaveStart'"));
    if (PlayerWaveStartSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerWaveStartSC = PlayerWaveStartSCLoaded.Object);
    
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerArialSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerArial.SC_PlayerArial'"));
    if (PlayerArialSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerArialSC = PlayerArialSCLoaded.Object);
    
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerHealedSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerHealed.SC_PlayerHealed'"));
    if (PlayerHealedSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerHealedSC = PlayerHealedSCLoaded.Object);
    
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerCritSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerCrit.SC_PlayerCrit'"));
    if (PlayerCritSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerCritSC = PlayerCritSCLoaded.Object);
    
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerRampageSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerRampage.SC_PlayerRampage'"));
    if (PlayerRampageSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerRampageSC = PlayerRampageSCLoaded.Object);
    
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerOverHeatLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerOverheat.SC_PlayerOverheat'"));
    if (PlayerRampageSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerOverHeatSC = PlayerOverHeatLoaded.Object);
    
    static ConstructorHelpers::FObjectFinder<USoundCue>PlayerAimLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerMiss.SC_PlayerMiss'"));
    if (PlayerRampageSCLoaded.Succeeded())
        PlayerVoiceLines.Emplace(PlayerMissSC = PlayerAimLoaded.Object);
    
    
#pragma endregion
#pragma region Narrator Voice Lines
    
    //Narrator voice lines SoundCues
    static ConstructorHelpers::FObjectFinder<USoundCue>NarratorDJumpLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorDoubleJump.SC_NarratorDoubleJump'"));
    if (NarratorDJumpLoaded.Succeeded())
        NarratorUpgradeDoubleJumpSC = NarratorDJumpLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>NarratorAFKUpgradeLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorAFKUpgrade.SC_NarratorAFKUpgrade'"));
    if (NarratorAFKUpgradeLoaded.Succeeded())
        NarratorAFKUpgradeSC = NarratorAFKUpgradeLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>NarratorHeavyHitLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorHeavyHit.SC_NarratorHeavyHit'"));
    if (NarratorHeavyHitLoaded.Succeeded())
        NarratorHeavyHitSC = NarratorHeavyHitLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>NarratorRampageLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorRampage.SC_NarratorRampage'"));
    if (NarratorRampageLoaded.Succeeded())
        NarratorRampageSC = NarratorRampageLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>NarratorRandomLoadedLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorRandom.SC_NarratorRandom'"));
    if (NarratorRandomLoadedLoaded.Succeeded())
        NarratorRampageSC = NarratorRandomLoadedLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>NarratorUpgradeOpenLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_UpgradeMenuOpen.SC_UpgradeMenuOpen'"));
    if (NarratorUpgradeOpenLoaded.Succeeded())
        NarratorUpgradeOpenSC = NarratorUpgradeOpenLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>NarratorWaveStartLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorWaveStart.SC_NarratorWaveStart'"));
    if (NarratorWaveStartLoaded.Succeeded())
        NarratorWaveStartSC = NarratorWaveStartLoaded.Object;

    static ConstructorHelpers::FObjectFinder<USoundCue>NarratorBarrelLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorBarrel.SC_NarratorBarrel'"));
    if (NarratorWaveStartLoaded.Succeeded())
        NarratorBarrelSC = NarratorBarrelLoaded.Object;

    static ConstructorHelpers::FObjectFinder<USoundCue>NarratorLoseLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorLose.SC_NarratorLose'"));
    if (NarratorWaveStartLoaded.Succeeded())
        NarratorLoseSC = NarratorLoseLoaded.Object;

    static ConstructorHelpers::FObjectFinder<USoundCue>NarratorWinLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorWin.SC_NarratorWin'"));
    if (NarratorWaveStartLoaded.Succeeded())
        NarratorWinSC = NarratorWinLoaded.Object;




    
#pragma endregion
#pragma region Ranger Voice Lines
    
    //Ranger Voice Lines
    
    static ConstructorHelpers::FObjectFinder<USoundCue>RangerAirHitLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Ranger/SC_RangerAirHit.SC_RangerAirHit'"));
    if (RangerAirHitLoaded.Succeeded())
        RangerAirHitSC = RangerAirHitLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>RangerDeathLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Ranger/SC_RangerDeath.SC_RangerDeath'"));
    if (RangerDeathLoaded.Succeeded())
        RangerDeathSC = RangerDeathLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>RangerHurtLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Ranger/SC_RangerHurt.SC_RangerHurt'"));
    if (RangerHurtLoaded.Succeeded())
        RangerHurtSC = RangerHurtLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>RangerKillLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Ranger/SC_RangerKill.SC_RangerKill'"));
    if (RangerKillLoaded.Succeeded())
        RangerKillsPlayerSC = RangerKillLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>RangerLockOnLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Ranger/SC_RangerLockOn.SC_RangerLockOn'"));
    if (RangerLockOnLoaded.Succeeded())
        RangerLockOnSC = RangerLockOnLoaded.Object;
    
#pragma endregion
#pragma region Grunt Voice Lines
    
    static ConstructorHelpers::FObjectFinder<USoundCue>GruntArialHitLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Grunt/SC_GruntArielHit.SC_GruntArielHit'"));
    if (GruntArialHitLoaded.Succeeded())
        GruntArialHitSC = GruntArialHitLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>GruntBarrelLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Grunt/SC_GruntBarrel.SC_GruntBarrel'"));
    if (GruntBarrelLoaded.Succeeded())
        GruntBarrelSC = GruntBarrelLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>GruntGrappelLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Grunt/SC_GruntGrapple.SC_GruntGrapple'"));
    if (GruntGrappelLoaded.Succeeded())
        GruntGrappleSC = GruntGrappelLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>GruntHurtLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Grunt/SC_GruntHurt.SC_GruntHurt'"));
    if (GruntHurtLoaded.Succeeded())
        GruntHurtSC = GruntHurtLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>GruntWaveStartLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Grunt/SC_GruntSpawn.SC_GruntSpawn'"));
    if (GruntWaveStartLoaded.Succeeded())
        GruntWaveStartSC = GruntWaveStartLoaded.Object;
    
    static ConstructorHelpers::FObjectFinder<USoundCue>GruntDeathLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Grunt/SC_GruntDeath.SC_GruntDeath'"));
    if (GruntWaveStartLoaded.Succeeded())
        GruntDeathSC = GruntDeathLoaded.Object;
    
    
#pragma endregion
    
}

void USoundManagerSubSystem::PlaySound(const FVector& Location, USoundBase* Sound) const
{
    if(Sound)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(),Sound, Location, 1, 1.0f);
    }
}

void USoundManagerSubSystem::PlaysMusic(USoundCue* Music) const
{
    if(Music)
    {
        UGameplayStatics::SpawnSound2D(GetWorld(),Music, 1,1,0,nullptr,true);
    }
}

void USoundManagerSubSystem::ResetEventTokens()
{
    PlayerSoundEventToken = 0;
    NarratorSoundEventToken = 0;
    SniperSoundEventToken = 0;
    GruntSoundEventToken = 0;
}

void USoundManagerSubSystem::PlaySniperSoundEvent(UAudioComponent* OwnerAC, int eventID)
{
    if(OwnerAC)
    {
        switch(eventID)
        {
            case 0 :
                SniperSoundEventToken += 50;
                if(SniperSoundEventToken >= 100)
                    if(RangerLockOnSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(RangerLockOnSC);
                            OwnerAC->Play();
                            SniperSoundEventToken -= 100;
                        }
                break;
            case 1 :
                SniperSoundEventToken += 10;
                if(SniperSoundEventToken >= 110)
                    if(RangerHurtSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(RangerHurtSC);
                            OwnerAC->Play();
                            SniperSoundEventToken -= 120;
                        }
                break;
            case 2:
                if(RangerDeathSC)
                {
                    if(OwnerAC->IsPlaying())
                    {
                        OwnerAC->Stop();
                        OwnerAC->SetSound(RangerDeathSC);
                        OwnerAC->Play();
                    }
                    else
                    {
                        OwnerAC->SetSound(RangerDeathSC);
                        OwnerAC->Play();
                    }
                }
                break;
            case 3:
                SniperSoundEventToken += 50;
                if(SniperSoundEventToken >= 80)
                    if(RangerAirHitSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(RangerAirHitSC);
                            OwnerAC->Play();
                            SniperSoundEventToken -= 90;
                        }
                break;
            case 4:
                if(RangerKillsPlayerSC){
                    if(OwnerAC->IsPlaying())
                    {
                        OwnerAC->Stop();
                        OwnerAC->SetSound(RangerKillsPlayerSC);
                        OwnerAC->Play();
                    }
                    else
                    {
                        OwnerAC->SetSound(RangerKillsPlayerSC);
                        OwnerAC->Play();
                    }
                }
                break;
            case 5:
                SniperSoundEventToken += 50;
                if(SniperSoundEventToken >= 80)
                    if(RangerFearSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(RangerFearSC);
                            OwnerAC->Play();
                            SniperSoundEventToken -= 90;
                        }
                break;
            case 6:
                SniperSoundEventToken += 50;
                if(SniperSoundEventToken >= 80)
                    if(RangerDisabledSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(RangerDisabledSC);
                            OwnerAC->Play();
                            SniperSoundEventToken -= 90;
                        }
                break;
            default:
                SniperSoundEventToken++;
                break;
        }
    }
}

void USoundManagerSubSystem::PlayGruntSoundEvent(UAudioComponent* OwnerAC, int eventID)
{
    if(OwnerAC)
    {
        switch(eventID)
        {
            case 0 :
                GruntSoundEventToken += 50;
                if(GruntSoundEventToken >= 100)
                    if(GruntArialHitSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(GruntArialHitSC);
                            OwnerAC->Play();
                            GruntSoundEventToken -= 100;
                        }
                break;
            case 1 :
                GruntSoundEventToken += 25;
                if(GruntSoundEventToken >= 75)
                    if(GruntBarrelSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(GruntBarrelSC);
                            OwnerAC->Play();
                            GruntSoundEventToken -= 75;
                        }
                break;
            case 2 :
                GruntSoundEventToken += 10;
                if(GruntSoundEventToken >= 110)
                    if(GruntHurtSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(GruntHurtSC);
                            OwnerAC->Play();
                            GruntSoundEventToken -= 110;
                        }
                break;
            case 3 :
                if(GruntBarrelSC)
                    if(!OwnerAC->IsPlaying())
                        if(FMath::RandRange(1, 6)== 1)
                        {
                            OwnerAC->SetSound(GruntBarrelSC);
                            OwnerAC->Play();
                        }
                break;
            case 4 :
                GruntSoundEventToken += 20;
                if(GruntSoundEventToken >= 60)
                    if(GruntWaveStartSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,FString::FromInt(GruntSoundEventToken));
                            OwnerAC->SetSound(GruntWaveStartSC);
                            OwnerAC->Play();
                            GruntSoundEventToken -= 60;
                            GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,FString::FromInt(GruntSoundEventToken));
                        }
                break;
            case 5 :
                if(GruntDeathSC)
                {
                    OwnerAC->SetSound(GruntDeathSC);
                    OwnerAC->Play();
                }
                break;
            default :
                GruntSoundEventToken ++;
                break;
        }
        
    }
}

void USoundManagerSubSystem::PlayNarratorSoundEvent(UAudioComponent* OwnerAC, int eventID)
{
    if(OwnerAC)
    {
        switch(eventID)
        {
            case 0 :
                if(NarratorUpgradeDoubleJumpSC){
                    if(OwnerAC->IsPlaying())
                    {
                        OwnerAC->Stop();
                        OwnerAC->SetSound(NarratorUpgradeDoubleJumpSC);
                        OwnerAC->Play();
                    }
                    else{
                        OwnerAC->SetSound(NarratorUpgradeDoubleJumpSC);
                        OwnerAC->Play();
                    }
                }
                
            case 1 :
                if(NarratorAFKUpgradeSC)
                    if(!OwnerAC->IsPlaying())
                    {
                        OwnerAC->SetSound(NarratorAFKUpgradeSC);
                        OwnerAC->Play();
                    }
                break;
                
            case 2 :
                NarratorSoundEventToken += 20;
                if(NarratorHeavyHitSC)
                    if(NarratorSoundEventToken >= 120){
                        if(OwnerAC->IsPlaying())
                        {
                            OwnerAC->Stop();
                            OwnerAC->SetSound(NarratorHeavyHitSC);
                            OwnerAC->Play();
                            NarratorSoundEventToken -= 135;
                        }
                        else{
                            OwnerAC->Play();
                        }
                    }
                break;
            case 3 :
                if(NarratorMaxGrappleSC)
                {
                    if(OwnerAC->IsPlaying())
                    {
                        OwnerAC->Stop();
                        OwnerAC->SetSound(NarratorMaxGrappleSC);
                        OwnerAC->Play();
                    }
                    else
                    {
                        OwnerAC->Play();
                    }
                }
                break;
            case 4 :
                if(FMath::RandRange(1, 6)== 1)
                {
                    if(NarratorMaxSpeedSC)
                    {
                        if(OwnerAC->IsPlaying())
                        {
                            OwnerAC->Stop();
                            OwnerAC->SetSound(NarratorMaxSpeedSC);
                            OwnerAC->Play();
                        }
                        else
                        {
                            OwnerAC->SetSound(NarratorMaxSpeedSC);
                            OwnerAC->Play();
                        }
                    }
                }
                break;
            case 5 :
                if(NarratorRampageSC)
                {
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(NarratorRampageSC);
                            OwnerAC->Play();
                        }
                    NarratorSoundEventToken -= 20;
                }
                break;
            case 6 :
                if(FMath::RandRange(1, 1)== 1)
                {
                    if(NarratorUpgradeOpenSC)
                    {
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(NarratorUpgradeOpenSC);
                            OwnerAC->Play();
                        }
                        else
                        {
                            OwnerAC->SetSound(NarratorUpgradeOpenSC);
                            OwnerAC->Play();
                        }
                    }
                }
                break;
            case 7 :
                if(NarratorRandomSC)
                    if(!OwnerAC->IsPlaying())
                    {
                        OwnerAC->SetSound(NarratorRandomSC);
                        OwnerAC->Play();
                    }
                break;
            case 8 :
                if(NarratorUpgradeSelectSC)
                    if(!OwnerAC->IsPlaying())
                    {
                        OwnerAC->SetSound(NarratorUpgradeSelectSC);
                        OwnerAC->Play();
                    }
                break;
            case 9 :
                if(NarratorWaveStartSC)
                    if(!OwnerAC->IsPlaying())
                    {
                        OwnerAC->SetSound(NarratorWaveStartSC);
                        OwnerAC->Play();
                    }
                break;
        case 10 :
            NarratorSoundEventToken += 50;
            if(NarratorBarrelSC)
            {
                if(NarratorSoundEventToken >= 85)
                {
                    if(!OwnerAC->IsPlaying())
                    {
                        OwnerAC->SetSound(NarratorBarrelSC);
                        OwnerAC->Play();
                        NarratorSoundEventToken -= 90;
                    }
                }
            }
            default :
                NarratorSoundEventToken++;
                break;
        }
    }
    
}

void USoundManagerSubSystem::PlayPlayerSoundEvent(UAudioComponent* OwnerAC, int eventID)
{
    if(OwnerAC)
    {
        switch(eventID)
        {
            case 0 :
                if(PlayerDeathSC)
                {
                    if(OwnerAC->IsPlaying())
                    {
                        OwnerAC->Stop();
                        OwnerAC->SetSound(PlayerDeathSC);
                        OwnerAC->Play();
                    }
                    else
                    {
                        OwnerAC->SetSound(PlayerDeathSC);
                        OwnerAC->Play();
                    }
                }
                break;
            case 1 :
                if(FMath::RandRange(1, 100)== 1)
                {
                    if(PlayerGrapplingSC)
                    {
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(PlayerGrapplingSC);
                            OwnerAC->Play();
                        }
                    }
                }
                break;
            case 2 :
                PlayerSoundEventToken += 10;
                if(PlayerSoundEventToken >= 100)
                {
                    if(PlayerHurtSC)
                    {
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(PlayerHurtSC);
                            OwnerAC->Play();
                            PlayerSoundEventToken -= 105;
                        }
                    }
                }
                break;
            case 3 :
                PlayerSoundEventToken += 40;
                if(PlayerSoundEventToken >= 100)
                {
                    if(PlayerHeavyHurtSC)
                    {
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(PlayerHeavyHurtSC);
                            OwnerAC->Play();
                            PlayerSoundEventToken -= 105;
                        }
                    }
                }
                break;
            case 4 :
                PlayerSoundEventToken += 30;
                if(PlayerSoundEventToken >= 70)
                    if(PlayerSniperHitSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(PlayerSniperHitSC);
                            OwnerAC->Play();
                            PlayerSoundEventToken -= 65;
                        }
                break;
            case 5 :
                if(PlayerAFKSC)
                    if(!OwnerAC->IsPlaying())
                    {
                        OwnerAC->SetSound(PlayerAFKSC);
                        OwnerAC->Play();
                    }
                break;
                
            case 6 :
                PlayerSoundEventToken += 20;
                if(PlayerSoundEventToken >= 70)
                    if(PlayerCritSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(PlayerCritSC);
                            OwnerAC->Play();
                            PlayerSoundEventToken -= 65;
                        }
                break;
                
            case 7 :
                if(PlayerWaveStartSC)
                    if(!OwnerAC->IsPlaying())
                    {
                        OwnerAC->SetSound(PlayerWaveStartSC);
                        OwnerAC->Play();
                    }
                break;
            case 8 :
                PlayerSoundEventToken += 60;
                if(PlayerSoundEventToken >= 120)
                    if(PlayerOverHeatSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(PlayerOverHeatSC);
                            OwnerAC->Play();
                            PlayerSoundEventToken -= 85;
                        }
                break;
            case 9 :
                PlayerSoundEventToken += 70;
                GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Cyan, "Arial kill");
                if(PlayerSoundEventToken >= 80)
                    if(PlayerArialSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(PlayerArialSC);
                            OwnerAC->Play();
                            PlayerSoundEventToken -= 85;
                        }
                break;
            case 10 :
                PlayerSoundEventToken += 40;
                if(PlayerSoundEventToken >= 80)
                    if(PlayerHealedSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(PlayerHealedSC);
                            OwnerAC->Play();
                            PlayerSoundEventToken -= 100;
                        }
                break;
            case 11 :
                if(FMath::RandRange(1,75) == 1)
                    if(PlayerMissSC)
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(PlayerMissSC);
                            OwnerAC->Play();
                        }
                break;
                
            case 12 :
                PlayerSoundEventToken += 15;
                if(PlayerSoundEventToken >= 95)
                {
                    if(PlayerHurtSC)
                    {
                        if(!OwnerAC->IsPlaying())
                        {
                            OwnerAC->SetSound(PlayerHurtSC);
                            OwnerAC->Play();
                            PlayerSoundEventToken -= 100;
                        }
                    }
                }
                break;
            case 13 :
                if(PlayerRampageSC)
                {
                    if(OwnerAC->IsPlaying())
                    {
                        OwnerAC->Stop();
                        OwnerAC->SetSound(PlayerRampageSC);
                        OwnerAC->Play();
                    }
                    else
                    {
                        OwnerAC->SetSound(PlayerRampageSC);
                        OwnerAC->Play();
                    }
                }
                break;
        case 14 :
            PlayerSoundEventToken += 10;
            if(PlayerSoundEventToken >= 90)
                if(PlayerHurtSC)
                    if(!OwnerAC->IsPlaying())
                    {
                        OwnerAC->SetSound(PlayerHurtSC);
                        OwnerAC->Play();
                        PlayerSoundEventToken -= 100;
                    }
            break;
            default :
                PlayerSoundEventToken ++;
                break;
        }
        
    }
}

void USoundManagerSubSystem::ToggleMusicOn(UAudioComponent* MusicAudioComp)
{
    if(MusicAudioComp->GetSound())
    {
        MusicAudioComp->Stop();
        MusicAudioComp->FadeIn(3.f,1.f,0.f,EAudioFaderCurve::Linear);
    }
}

void USoundManagerSubSystem::ToggleMusicOff(UAudioComponent* MusicAudioComp)
{
    if(MusicAudioComp->GetSound())
        MusicAudioComp->FadeOut(3.f,0.0f,EAudioFaderCurve::Linear);
}

void USoundManagerSubSystem::WaveStart(AActor* Actor)
{
    UGameplayStatics::PlaySound2D(Actor->GetWorld(),WaveStartSound);
}







