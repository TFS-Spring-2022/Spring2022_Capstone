// Created by Spring2022_Capstone team


#include "SniperDisableTrigger.h"

ASniperDisableTrigger::ASniperDisableTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ASniperDisableTrigger::OnOverlapBegin);
}


void ASniperDisableTrigger::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	// If player character has the disable bomb.
	if(SniperToDisable && OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if(Player->GetHasSniperDisableObject())
		{
			SniperToDisable->DisableSniperEnemy();
			Player->SetHasSniperDisableObject(false);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Player doesn't not have disable device");
		}
	}
}
