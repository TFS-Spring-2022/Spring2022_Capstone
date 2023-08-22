// Created by Spring2022_Capstone team


#include "UpgradeSystemComponent.h"

#include "GrappleComponent.h"
#include "PlayerCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
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
	if(UpgradeMenuWidgetInstance && UpgradeChoices.Num() > 0)
	{
		// Remove Player's movement and attacking.
		PlayerController->SetIgnoreLookInput(true);
		PlayerController->SetIgnoreMoveInput(true);
		PlayerToUpgrade->SetCanAttack(false);
		// Start slow motion
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), PausedTimeDilation);
		PrepareUpgradeChoices();
		// Show mouse cursor and set input to only effect UI.
		PlayerController->bShowMouseCursor = true;
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, UpgradeMenuWidgetInstance, EMouseLockMode::LockAlways, false); // flush input false because want to maintain movement
		// Open Upgrade Menu.
		UpgradeMenuWidgetInstance->AddToViewport(0);
		bIsMenuOpen = true;
		PlayerToUpgrade->GetPlayerHUD()->SetVisibility(ESlateVisibility::Hidden);
	}


}

void UUpgradeSystemComponent::CloseUpgradeMenu()
{
	if(UpgradeMenuWidgetInstance)
	{
		// Return Player's movement and attacking.
		PlayerController->SetIgnoreLookInput(false);
		PlayerController->SetIgnoreMoveInput(false);
		PlayerToUpgrade->SetCanAttack(true);
		// End slow motion.
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
		// Hide mouse cursor and return InputMode to only effect Game.
		PlayerController->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController, false);
		// Close Upgrade Menu.
		UpgradeMenuWidgetInstance->RemoveFromParent();
		bIsMenuOpen = false;
		// Clear from delegate's invocation list.
		UpgradeMenuWidgetInstance->GetUpgrade1Button()->OnClicked.Clear();
		UpgradeMenuWidgetInstance->GetUpgrade2Button()->OnClicked.Clear();
		UpgradeMenuWidgetInstance->GetUpgrade3Button()->OnClicked.Clear();

		PlayerToUpgrade->GetPlayerHUD()->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUpgradeSystemComponent::PrepareUpgradeChoices()
{
	// ToDo/Note: Text will not be in final version. Add Images of cards to display relevant upgrade information.

	if(UpgradeChoices.Num() >= 3)
	{
		// Set UpgradeChoices
		UpgradeChoice1 = GetUpgradeChoice();
		const FString UpgradeChoice1FString = FString::Printf(TEXT("%s + %s"), *GetUpgradeEnumValueText(UpgradeChoice1.TypeOfUpgrade), *FString::SanitizeFloat(UpgradeChoice1.UpgradeValue, 1));
		UpgradeMenuWidgetInstance->SetUpgradeTextBox(1, FText::FromString(UpgradeChoice1FString));
		// Upgrade 2
		UpgradeChoice2 = GetUpgradeChoice();
		const FString UpgradeChoice2FString = FString::Printf(TEXT("%s + %s"), *GetUpgradeEnumValueText(UpgradeChoice2.TypeOfUpgrade), *FString::SanitizeFloat(UpgradeChoice2.UpgradeValue, 1));
		UpgradeMenuWidgetInstance->SetUpgradeTextBox(2, FText::FromString(UpgradeChoice2FString));
		// Upgrade3
		UpgradeChoice3 = GetUpgradeChoice();
		const FString UpgradeChoice3FString = FString::Printf(TEXT("%s + %s"), *GetUpgradeEnumValueText(UpgradeChoice3.TypeOfUpgrade), *FString::SanitizeFloat(UpgradeChoice3.UpgradeValue, 1));
		UpgradeMenuWidgetInstance->SetUpgradeTextBox(3, FText::FromString(UpgradeChoice3FString));

		UpgradeMenuWidgetInstance->GetUpgrade1Button()->OnClicked.AddDynamic(this, &UUpgradeSystemComponent::ApplyUpgrade1);
		UpgradeMenuWidgetInstance->GetUpgrade2Button()->OnClicked.AddDynamic(this, &UUpgradeSystemComponent::ApplyUpgrade2);
		UpgradeMenuWidgetInstance->GetUpgrade3Button()->OnClicked.AddDynamic(this, &UUpgradeSystemComponent::ApplyUpgrade3);	
	}
	else if(UpgradeChoices.Num() == 2)
	{
		// When there are only two available upgrades, hid the third button and text.
		// Upgrade 1
		UpgradeChoice1 = GetUpgradeChoice();
		const FString UpgradeChoice1FString = FString::Printf(TEXT("%s + %s"), *GetUpgradeEnumValueText(UpgradeChoice1.TypeOfUpgrade), *FString::SanitizeFloat(UpgradeChoice1.UpgradeValue, 1));
		UpgradeMenuWidgetInstance->SetUpgradeTextBox(1, FText::FromString(UpgradeChoice1FString));
		// Upgrade 2
		UpgradeChoice2 = GetUpgradeChoice();
		const FString UpgradeChoice2FString = FString::Printf(TEXT("%s + %s"), *GetUpgradeEnumValueText(UpgradeChoice2.TypeOfUpgrade), *FString::SanitizeFloat(UpgradeChoice2.UpgradeValue, 1));
		UpgradeMenuWidgetInstance->SetUpgradeTextBox(2, FText::FromString(UpgradeChoice2FString));
		UpgradeMenuWidgetInstance->GetUpgrade1Button()->OnClicked.AddDynamic(this, &UUpgradeSystemComponent::ApplyUpgrade1);
		UpgradeMenuWidgetInstance->GetUpgrade2Button()->OnClicked.AddDynamic(this, &UUpgradeSystemComponent::ApplyUpgrade2);
		// Remove Upgrade3Button as it has no upgrade choice. ToDo/Note: Using collapsed will allow us to automatically reposition upgrade cards when the art is added.
		UpgradeMenuWidgetInstance->GetUpgrade3Button()->SetVisibility(ESlateVisibility::Collapsed);
		UpgradeMenuWidgetInstance->SetUpgradeTextBoxVisibility(3, ESlateVisibility::Collapsed);
	}
	else if(UpgradeChoices.Num() == 1)
	{
		// When there is only one available upgrades, hid the second button and text.
		// Upgrade 1
		UpgradeChoice1 = GetUpgradeChoice();
		const FString UpgradeChoice1FString = FString::Printf(TEXT("%s + %s"), *GetUpgradeEnumValueText(UpgradeChoice1.TypeOfUpgrade), *FString::SanitizeFloat(UpgradeChoice1.UpgradeValue, 1));
		UpgradeMenuWidgetInstance->SetUpgradeTextBox(1, FText::FromString(UpgradeChoice1FString));
		UpgradeMenuWidgetInstance->GetUpgrade1Button()->OnClicked.AddDynamic(this, &UUpgradeSystemComponent::ApplyUpgrade1);
		//Remove Upgrade2Button as it has no upgrade choice. ToDo/Note: Using collapsed will allow us to automatically reposition upgrade cards when the art is added.
		UpgradeMenuWidgetInstance->GetUpgrade2Button()->SetVisibility(ESlateVisibility::Collapsed);
		UpgradeMenuWidgetInstance->SetUpgradeTextBoxVisibility(2, ESlateVisibility::Collapsed);
	}
	else
	{
		// When there are no available upgrades, close Upgrade Menu.
		UpgradeMenuWidgetInstance->GetUpgrade1Button()->SetVisibility(ESlateVisibility::Collapsed);
		UpgradeMenuWidgetInstance->SetUpgradeTextBoxVisibility(1, ESlateVisibility::Collapsed);
		CloseUpgradeMenu();
	}
	

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

FString UUpgradeSystemComponent::GetUpgradeEnumValueText(const int Value) const
{
	switch (Value)
	{
	case 0:
		return "None";
	case 1:
		return "Max Charge Amount";
	case 2:
		return "Weapon Damage";
	case 3:
		return "Charge Cooldown";
	case 4:
		return "Max Health";
	case 5:
		return "Movement Speed";
	case 6:
		return "Grapple Cooldown";
	case 7:
		return "Unlock Double Jump";
	default:
		return "Error! Value out of range";
	}
}
