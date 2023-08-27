// Created by Spring2022_Capstone team


#include "SoundManagerSubSystem.h"

#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

USoundManagerSubSystem::USoundManagerSubSystem()
{
	SubSystemAudio = CreateDefaultSubobject<UAudioComponent>("GrappleShotAC");
	
}

void USoundManagerSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GEngine->AddOnScreenDebugMessage(-1, 5.f ,FColor::Black,"Done");
    PlayerDeathSC = LoadObject<USoundCue>(nullptr,nullptr, TEXT("D:/Unreal/Capstone/Content/Blueprints/Audio/Ambience/BP_JungleAmbience.uasset"), LOAD_None, NULL);
   // PlayerVoiceLines.Add(PlayerDeathSC);
	
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






