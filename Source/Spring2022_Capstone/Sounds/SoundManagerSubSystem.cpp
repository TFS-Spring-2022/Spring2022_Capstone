// Created by Spring2022_Capstone team


#include "SoundManagerSubSystem.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

USoundManagerSubSystem::USoundManagerSubSystem()
{
	SubSystemAudio = CreateDefaultSubobject<UAudioComponent>("GrappleShotAC");


#pragma region PlayerVoiceLines

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






