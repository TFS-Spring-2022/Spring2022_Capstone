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
		PrepareUpgradeChoices();
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

		// Clear from delegate's invocation list.
		UpgradeMenuWidgetInstance->GetUpgrade1Button()->OnClicked.Clear();
		UpgradeMenuWidgetInstance->GetUpgrade2Button()->OnClicked.Clear();
		UpgradeMenuWidgetInstance->GetUpgrade3Button()->OnClicked.Clear();
		
	}
}

void UUpgradeSystemComponent::PrepareUpgradeChoices()
{
	UpgradeChoice1 = GetUpgradeChoice();
	UpgradeChoice2 = GetUpgradeChoice();
	UpgradeChoice3 = GetUpgradeChoice();

	UpgradeMenuWidgetInstance->GetUpgrade1Button()->OnClicked.AddDynamic(this, &UUpgradeSystemComponent::ApplyUpgrade1);
	UpgradeMenuWidgetInstance->GetUpgrade2Button()->OnClicked.AddDynamic(this, &UUpgradeSystemComponent::ApplyUpgrade2);
	UpgradeMenuWidgetInstance->GetUpgrade3Button()->OnClicked.AddDynamic(this, &UUpgradeSystemComponent::ApplyUpgrade3);
	
	// ToDo: Change text of buttons (temporary until art made)
}

FUpgradeChoice UUpgradeSystemComponent::GetUpgradeChoice()
{
	const FUpgradeChoice RandomlySelectedUpgrade = UpgradeChoices[FMath::RandRange(0, UpgradeChoices.Num() - 1)];
	return RandomlySelectedUpgrade;
}


void UUpgradeSystemComponent::ApplyUpgrade1()
{

	// ToDo: Random weapon selection to upgrade (RandRang and GetWeapon());
	switch (UpgradeChoice1.TypeOfUpgrade)
	{
	case EUpgradeType::MaxChargeAmount:
		IncreaseMaxChargeAmount(PlayerToUpgrade->GetActiveWeapon(), UpgradeChoice1.UpgradeValue);
		break;
	case EUpgradeType::WeaponDamage:
		IncreaseWeaponDamageByAmount(PlayerToUpgrade->GetActiveWeapon(), UpgradeChoice1.UpgradeValue);
		break;
	case EUpgradeType::ChargeCooldown:
		IncreaseChargeCooldownRate(PlayerToUpgrade->GetActiveWeapon(), UpgradeChoice1.UpgradeValue);
		break;
	case EUpgradeType::MaxHealth:
		IncreaseMaxHealthByAmount(UpgradeChoice1.UpgradeValue);
		break;
	case EUpgradeType::MovementSpeed:
		IncreaseMovementSpeedByAmount(UpgradeChoice1.UpgradeValue);
		break;
	case EUpgradeType::GrappleCooldown:
		DecreaseGrappleCooldownBySeconds(UpgradeChoice1.UpgradeValue);
		break;
	case EUpgradeType::UnlockDoubleJump:
		UnlockDoubleJump();
		break;
	default: ;
	}

	RemoveUpgradeChoice(UpgradeChoice1.UniqueID);
	CloseUpgradeMenu();
}

void UUpgradeSystemComponent::ApplyUpgrade2()
{
	
	// ToDo: Random weapon selection to upgrade (RandRang and GetWeapon());
	switch (UpgradeChoice2.TypeOfUpgrade)
	{
	case EUpgradeType::MaxChargeAmount:
		IncreaseMaxChargeAmount(PlayerToUpgrade->GetActiveWeapon(), UpgradeChoice2.UpgradeValue);
		break;
	case EUpgradeType::WeaponDamage:
		IncreaseWeaponDamageByAmount(PlayerToUpgrade->GetActiveWeapon(), UpgradeChoice2.UpgradeValue);
		break;
	case EUpgradeType::ChargeCooldown:
		IncreaseChargeCooldownRate(PlayerToUpgrade->GetActiveWeapon(), UpgradeChoice2.UpgradeValue);
		break;
	case EUpgradeType::MaxHealth:
		IncreaseMaxHealthByAmount(UpgradeChoice2.UpgradeValue);
		break;
	case EUpgradeType::MovementSpeed:
		IncreaseMovementSpeedByAmount(UpgradeChoice2.UpgradeValue);
		break;
	case EUpgradeType::GrappleCooldown:
		DecreaseGrappleCooldownBySeconds(UpgradeChoice2.UpgradeValue);
		break;
	case EUpgradeType::UnlockDoubleJump:
		UnlockDoubleJump();
		break;
	default: ;
	}

	RemoveUpgradeChoice(UpgradeChoice2.UniqueID);
	CloseUpgradeMenu();
}

void UUpgradeSystemComponent::ApplyUpgrade3()
{
	
	// ToDo: Random weapon selection to upgrade (RandRang and GetWeapon());
	switch (UpgradeChoice3.TypeOfUpgrade)
	{
	case EUpgradeType::MaxChargeAmount:
		IncreaseMaxChargeAmount(PlayerToUpgrade->GetActiveWeapon(), UpgradeChoice3.UpgradeValue);
		break;
	case EUpgradeType::WeaponDamage:
		IncreaseWeaponDamageByAmount(PlayerToUpgrade->GetActiveWeapon(), UpgradeChoice3.UpgradeValue);
		break;
	case EUpgradeType::ChargeCooldown:
		IncreaseChargeCooldownRate(PlayerToUpgrade->GetActiveWeapon(), UpgradeChoice3.UpgradeValue);
		break;
	case EUpgradeType::MaxHealth:
		IncreaseMaxHealthByAmount(UpgradeChoice1.UpgradeValue);
		break;
	case EUpgradeType::MovementSpeed:
		IncreaseMovementSpeedByAmount(UpgradeChoice1.UpgradeValue);
		break;
	case EUpgradeType::GrappleCooldown:
		DecreaseGrappleCooldownBySeconds(UpgradeChoice1.UpgradeValue);
		break;
	case EUpgradeType::UnlockDoubleJump:
		UnlockDoubleJump();
		break;
	default: ;
	}

	RemoveUpgradeChoice(UpgradeChoice3.UniqueID);
	CloseUpgradeMenu();
}

void UUpgradeSystemComponent::RemoveUpgradeChoice(const int ID)
{
	int i = 0;
	for (const FUpgradeChoice Choice : UpgradeChoices)
	{
		if(Choice.UniqueID == ID)
		{
			UpgradeChoices.RemoveAt(i);
			break;
		}
		i++;
	}
}
