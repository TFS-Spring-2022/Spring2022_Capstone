// Created by Spring2022_Capstone team


#include "UpgradeSystemComponent.h"

#include "PlayerCharacter.h"
#include "Spring2022_Capstone/HealthComponent.h"

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

	PlayerToUpgrade = Cast<APlayerCharacter>(GetOwner());	

}


// Called every frame
void UUpgradeSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUpgradeSystemComponent::IncreaseMaxChargeAmount(AWeaponBase* WeaponToUpgrade, float IncrementAmount)
{
	if(WeaponToUpgrade)
	{
		WeaponToUpgrade->MaxChargeAmount += IncrementAmount;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("%s Max Charge Amount Increased"), *WeaponToUpgrade->GetName()));
	}
}

void UUpgradeSystemComponent::IncreaseMaxHealthByAmount(float IncrementAmount)
{
	if(PlayerToUpgrade)
	{
		PlayerToUpgrade->HealthComponent->SetMaxHealth(PlayerToUpgrade->HealthComponent->GetMaxHealth() + IncrementAmount);
		PlayerToUpgrade->HealthComponent->SetHealth(PlayerToUpgrade->HealthComponent->GetHealth() + IncrementAmount);
		GEngine->AddOnScreenDebugMessage(0, 4.f, FColor::Red, FString::Printf(TEXT("Your new max health is: %f"), PlayerToUpgrade->HealthComponent->GetMaxHealth()));
	}
}

void UUpgradeSystemComponent::IncreaseMaxHealthByPercentage(float PercentageAmount)
{
	float HealthIncrease = PlayerToUpgrade->HealthComponent->GetMaxHealth() * PercentageAmount / 100;
	PlayerToUpgrade->HealthComponent->SetMaxHealth(PlayerToUpgrade->HealthComponent->GetMaxHealth() + HealthIncrease);
	PlayerToUpgrade->HealthComponent->SetHealth(PlayerToUpgrade->HealthComponent->GetHealth() + HealthIncrease);
	GEngine->AddOnScreenDebugMessage(0, 4.f, FColor::Red, FString::Printf(TEXT("Your new max health is: %f"), PlayerToUpgrade->HealthComponent->GetMaxHealth()));
}

void UUpgradeSystemComponent::IncreaseMovementSpeedByAmount(int Value)
{
	PlayerToUpgrade->Speed += Value;
	GEngine->AddOnScreenDebugMessage(0, 4.f, FColor::Red, FString::Printf(TEXT("Your new Movement Speed is: %f"), PlayerToUpgrade->Speed));
}

