// Created by Spring2022_Capstone team


#include "RecoilComponent.h"

// Sets default values for this component's properties
URecoilComponent::URecoilComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void URecoilComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningParentWeapon = Cast<AWeaponBase>(GetOwner()); 
	OwnersPlayerController = GetWorld()->GetFirstPlayerController();
	
}

// Called every frame
void URecoilComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}
