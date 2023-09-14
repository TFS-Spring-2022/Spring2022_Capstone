// Created by Spring2022_Capstone team


#include "SniperDisablePickup.h"

#include "Spring2022_Capstone/Player/PlayerCharacter.h"

ASniperDisablePickup::ASniperDisablePickup()
{
	PickupStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Pickup Mesh");
	SetRootComponent(PickupStaticMesh);
	OnActorBeginOverlap.AddDynamic(this, &ASniperDisablePickup::OnOverlapBegin);
}

void ASniperDisablePickup::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	// If the player walks over object, set status in character and delete object. 
	if(OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		Cast<APlayerCharacter>(OtherActor)->SetHasSniperDisableObject(true);
		Destroy();
	}
}
