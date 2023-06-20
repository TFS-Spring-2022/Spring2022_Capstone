// Created by Spring2022_Capstone team


#include "UpgradeSystemComponent.h"

// Sets default values for this component's properties
UUpgradeSystemComponent::UUpgradeSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UUpgradeSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUpgradeSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUpgradeSystemComponent::UpgradeMaxChargeAmount(AWeaponBase* WeaponToUpgrade, float IncrementAmount)
{
	if(WeaponToUpgrade)
	{
		WeaponToUpgrade->MaxChargeAmount += IncrementAmount;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("%s Max Charge Amount Increased"), *WeaponToUpgrade->GetName()));
	}
}

void UUpgradeSystemComponent::UpgradeMaxHealth(APlayerCharacter* Character, float IncrementAmount)
{
}

