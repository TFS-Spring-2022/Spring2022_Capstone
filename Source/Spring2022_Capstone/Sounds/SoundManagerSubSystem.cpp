// Created by Spring2022_Capstone team


#include "SoundManagerSubSystem.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

USoundManagerSubSystem::USoundManagerSubSystem()
{
	SubSystemAudio = CreateDefaultSubobject<UAudioComponent>("GrappleShotAC");


#pragma region Player Voice Lines

	//Player voice lines SoundCues 
	static ConstructorHelpers::FObjectFinder<USoundCue>PlayerDeathSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerDeath.SC_PlayerDeath'"));
	if (PlayerDeathSCLoaded.Succeeded())
		PlayerDeathSC = PlayerDeathSCLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>PlayerGrapplingSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/Guns/SC_Overheat.SC_Overheat'"));
	if (PlayerGrapplingSCLoaded.Succeeded())
		PlayerGrapplingSC = PlayerGrapplingSCLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>PlayerHurtSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/Guns/SC_Overheat.SC_Overheat'"));
	if (PlayerHurtSCLoaded.Succeeded())
		PlayerHurtSC = PlayerHurtSCLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>PlayerHeavyHurSCtLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/Guns/SC_Overheat.SC_Overheat'"));
	if (PlayerHeavyHurSCtLoaded.Succeeded())
		PlayerHeavyHurtSC = PlayerHeavyHurSCtLoaded.Object;
	
	static ConstructorHelpers::FObjectFinder<USoundCue>PlayerSniperSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/Guns/SC_Overheat.SC_Overheat'"));
	if (PlayerSniperSCLoaded.Succeeded())
		PlayerSniperHitSC = PlayerSniperSCLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>PlayerAFKSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerAFK.SC_PlayerAFK'"));
	if (PlayerAFKSCLoaded.Succeeded())
		PlayerAFKSC = PlayerAFKSCLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>PlayerWaveStartSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/Guns/SC_Overheat.SC_Overheat'"));
	if (PlayerWaveStartSCLoaded.Succeeded())
		PlayerWaveStartSC = PlayerWaveStartSCLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>PlayerArialSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerArial.SC_PlayerArial'"));
	if (PlayerArialSCLoaded.Succeeded())
		PlayerArialSC = PlayerArialSCLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>PlayerHealedSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/Guns/SC_Overheat.SC_Overheat'"));
	if (PlayerHealedSCLoaded.Succeeded())
		PlayerHealedSC = PlayerHealedSCLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>PlayerCritSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Player/SC_PlayerCrit.SC_PlayerCrit'"));
    	if (PlayerCritSCLoaded.Succeeded())
    		PlayerCritSC = PlayerCritSCLoaded.Object;
    		
	static ConstructorHelpers::FObjectFinder<USoundCue>PlayerRampageSCLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/Guns/SC_Overheat.SC_Overheat'"));
	if (PlayerRampageSCLoaded.Succeeded())
		PlayerRampageSC = PlayerRampageSCLoaded.Object;

	
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

	static ConstructorHelpers::FObjectFinder<USoundCue>NarratorMaxGrappleLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorMaxGrapple.SC_NarratorMaxGrapple'"));
	if (NarratorMaxGrappleLoaded.Succeeded())
		NarratorMaxGrappleSC = NarratorMaxGrappleLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>NarratorMaxSpeedLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorMaxSpeed.SC_NarratorMaxSpeed'"));
	if (NarratorMaxSpeedLoaded.Succeeded())
		NarratorMaxSpeedSC = NarratorMaxSpeedLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>NarratorRampageLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorRampage.SC_NarratorRampage'"));
	if (NarratorRampageLoaded.Succeeded())
		NarratorRampageSC = NarratorRampageLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>NarratorRandomLoadedLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorRandom.SC_NarratorRandom'"));
	if (NarratorRandomLoadedLoaded.Succeeded())
		NarratorRampageSC = NarratorRandomLoadedLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>NarratorUpgradeOpenLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorUpgradeOpen.SC_NarratorUpgradeOpen'"));
	if (NarratorUpgradeOpenLoaded.Succeeded())
		NarratorUpgradeOpenSC = NarratorUpgradeOpenLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>NarratorUpgradeSelectLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorUpgradeSelect.SC_NarratorUpgradeSelect'"));
	if (NarratorUpgradeSelectLoaded.Succeeded())
		NarratorUpgradeSelectSC = NarratorUpgradeSelectLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>NarratorWaveStartLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Narrator/SC_NarratorWaveStart.SC_NarratorWaveStart'"));
	if (NarratorWaveStartLoaded.Succeeded())
		NarratorWaveStartSC = NarratorWaveStartLoaded.Object;
	
	
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
	
	static ConstructorHelpers::FObjectFinder<USoundCue>RangerJumpLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Ranger/SC_RangerJump.SC_RangerJump'"));
	if (RangerJumpLoaded.Succeeded())
		RangerJumpSC = RangerJumpLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>RangerKillLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Ranger/SC_RangerKill.SC_RangerKill'"));
	if (RangerKillLoaded.Succeeded())
		RangerKillsPlayerSC = RangerKillLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>RangerLockOnLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Ranger/SC_RangerLockOn.SC_RangerLockOn'"));
	if (RangerLockOnLoaded.Succeeded())
		RangerLockOnSC = RangerLockOnLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>RangerRandomLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Ranger/SC_RangerRandom.SC_RangerRandom'"));
	if (RangerRandomLoaded.Succeeded())
		RangerRandomSC = RangerRandomLoaded.Object;
	
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

	static ConstructorHelpers::FObjectFinder<USoundCue>GruntWaveStartLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Grunt/SC_GruntJump.SC_GruntJump'"));
	if (GruntWaveStartLoaded.Succeeded())
		GruntWaveStartSC = GruntWaveStartLoaded.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>GruntNumbersLoaded(TEXT("/Script/Engine.SoundCue'/Game/Blueprints/Audio/SoundCues/VoiceLines/Grunt/SC_GruntNumbers.SC_GruntNumbers'"));
	if (GruntNumbersLoaded.Succeeded())
		GruntNumbersSC = GruntNumbersLoaded.Object;

	
#pragma endregion 
	
}


void USoundManagerSubSystem::PlaySound(const FVector& Location, USoundBase* Sound) const
{
	if(Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location, 1.0f, 1.0f,0.0f);
	}
}

void USoundManagerSubSystem::PlaysMusic(const USoundCue* Music) const
{
	if(Music)
	{
		
	}
}

void USoundManagerSubSystem::PlaySoundEvent() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f ,FColor::Black,"PlaySoundEventCalled");
	if(PlayerDeathSC)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f ,FColor::Black,"PlayerDS");
		PlaySound(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(),PlayerDeathSC);
	}
}

void USoundManagerSubSystem::ImplementToken(int stk1, int ptk2, int gtk3, int sntk, int ntk)
{
	SoundEventToken += stk1;
	PlayerSoundEventToken += ptk2;
	GruntSoundEventToken += gtk3;
	SniperSoundEventToken += sntk;
	NarratorSoundEventToken += ntk;
}






