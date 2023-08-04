// Created by Spring2022_Capstone team


#include "SoundManagerSubSystem.h"

#include "Kismet/GameplayStatics.h"

USoundManagerSubSystem::USoundManagerSubSystem()
{
	
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




