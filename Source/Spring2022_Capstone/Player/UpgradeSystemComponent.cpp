// Created by Spring2022_Capstone team


#include "UpgradeSystemComponent.h"

#include "GrappleComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/HealthComponent.h"

// Sets default values for this component's properties
UUpgradeSystemComponent::UUpgradeSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}


// Called when the game starts
void UUpgradeSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerToUpgrade = Cast<APlayerCharacter>(GetOwner());

	if(UpgradeMenuWidgetBP)
		UpgradeMenuWidgetInstance = Cast<UUpgradeMenuWidget>(CreateWidget(GetWorld(), UpgradeMenuWidgetBP));

	bIsMenuOpen = false;

	PlayerController = GetWorld()->GetFirstPlayerController();

}


// Called every frame
void UUpgradeSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UUpgradeSystemComponent::IncreaseMaxChargeAmount(AWeaponBase* WeaponToUpgrade, float Amount)
{
	if(WeaponToUpgrade)
	{
		WeaponToUpgrade->MaxChargeAmount += Amount;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("%s Max Charge Amount Increased"), *WeaponToUpgrade->GetName()));
	}
}

void UUpgradeSystemComponent::IncreaseMaxHealthByAmount(float Amount)
{
	if(PlayerToUpgrade)
	{
		PlayerToUpgrade->HealthComponent->SetMaxHealth(PlayerToUpgrade->HealthComponent->GetMaxHealth() + Amount);
		PlayerToUpgrade->HealthComponent->SetHealth(PlayerToUpgrade->HealthComponent->GetHealth() + Amount);
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

void UUpgradeSystemComponent::IncreaseMovementSpeedByAmount(int Amount)
{
	PlayerToUpgrade->Speed += Amount;
	GEngine->AddOnScreenDebugMessage(0, 4.f, FColor::Red, FString::Printf(TEXT("Your new Movement Speed is: %f"), PlayerToUpgrade->Speed));
}

void UUpgradeSystemComponent::IncreaseWeaponDamageByAmount(AWeaponBase* WeaponToUpgrade, float Amount)
{
	if(WeaponToUpgrade)
	{
		WeaponToUpgrade->SetDamage(WeaponToUpgrade->GetDamage() + Amount);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("%s Damage is now: %f"), *WeaponToUpgrade->GetName(), WeaponToUpgrade->GetDamage()));
	}
}

void UUpgradeSystemComponent::UnlockDoubleJump()
{
	PlayerToUpgrade->JumpMaxCount = PlayerToUpgrade->JumpMaxCount == 1 ? 2 : 1;
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, FString::Printf(TEXT("Your max jumps are: %i"), PlayerToUpgrade->JumpMaxCount));
}

void UUpgradeSystemComponent::DecreaseGrappleCooldownBySeconds(const float Seconds)
{
	PlayerToUpgrade->GrappleComponent->DecrementGrappleCooldown(Seconds);
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, FString::Printf(TEXT("Your grapple cooldown is: %f"), PlayerToUpgrade->GrappleComponent->GetCooldown()));
}

void UUpgradeSystemComponent::IncreaseChargeCooldownRate(AWeaponBase* WeaponToUpgrade, float Amount)
{
	WeaponToUpgrade->ChargeCooldownRate += Amount;
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, FString::Printf(TEXT("%s Charge cooldown rate is: %f"), *WeaponToUpgrade->GetName(), WeaponToUpgrade->ChargeCooldownRate));
}

void UUpgradeSystemComponent::OpenUpgradeMenu()
{
	if(UpgradeMenuWidgetInstance)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		PlayerController->bShowMouseCursor = true;
		UpgradeMenuWidgetInstance->AddToViewport(0);
		bIsMenuOpen = true;
	}
}

void UUpgradeSystemComponent::CloseUpgradeMenu()
{
	if(UpgradeMenuWidgetInstance)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		PlayerController->bShowMouseCursor = false;
		UpgradeMenuWidgetInstance->RemoveFromParent();
		bIsMenuOpen = false;
	}
}


