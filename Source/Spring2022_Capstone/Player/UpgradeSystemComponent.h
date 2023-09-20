// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/Image.h"
#include "Spring2022_Capstone/UI/UpgradeMenu/UpgradeMenuWidget.h"
#include "Spring2022_Capstone/Weapon/WeaponBase.h"
#include "UpgradeSystemComponent.generated.h"

UENUM()
enum EUpgradeType
{
	None,
	MaxChargeAmount,
	WeaponDamage,
	ChargeCooldown,
	MaxHealth,
	MovementSpeed,
	GrappleCooldown,
	UnlockDoubleJump,
	// ToDo: Ability Cooldown
	// ToDo: Grapple Range
	// ToDo: Dash Distance
	// ToDo: Crit Hit Multiplier
};

USTRUCT()
struct FUpgradeChoice
{
	GENERATED_BODY()
	FUpgradeChoice()
	{
		UniqueID = FMath::RandRange(0, 1024);
		TypeOfUpgrade = EUpgradeType::None;
		UpgradeValue = 0;
		UpgradeImage = nullptr;
	}

	FUpgradeChoice(const int Identifier, const EUpgradeType Type, const float Value,UTexture* Image)
	{
		UniqueID = Identifier;
		TypeOfUpgrade = Type;
		UpgradeValue = Value;
		UpgradeImage = Image;
	}
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EUpgradeType> TypeOfUpgrade;

	UPROPERTY(EditAnywhere)
	float UpgradeValue;

	// Used to remove upgrade from UpgradeChoices 
	UPROPERTY(EditAnywhere)
	int UniqueID;

	UPROPERTY(EditAnywhere)
	UTexture* UpgradeImage;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Within=(PlayerCharacter))
class SPRING2022_CAPSTONE_API UUpgradeSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUpgradeSystemComponent();
	
	// Widget Blue Print used to create instance for Player's upgrade menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUpgradeMenuWidget> UpgradeMenuWidgetBP;

	UPROPERTY()
	UUpgradeMenuWidget* UpgradeMenuWidgetInstance;

	UPROPERTY()
	USoundManagerSubSystem* SoundManagerSubSystem;

	UPROPERTY(EditAnywhere, Category = "Purchase Sound")
	USoundCue* PurchaseSC;

	UPROPERTY()
	UScoreSystemTimerSubSystem* ScoreSystemTimerSubSystem;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	APlayerCharacter* PlayerToUpgrade;
	
	UPROPERTY()
	APlayerController* PlayerController;

	// GlobalTimeDilation value when the Upgrade Menu is opened.
	UPROPERTY(EditAnywhere, Category = "UI")
	float PausedTimeDilation = 0.05;


	//Sounds
	bool bUpgradeTimerAFKStarted = false;
	float UpgradeTimerAFK = 0.0f;

	const float AFK_TIME_TRIGGER = 10.f;

	FTimerHandle StartNextRoundTimerHandle;
	float StartNextRoundDelayBuffer = 1.0f; // Time before starting next round

	// Calls UEnemyWaveManagementSystem::StartNextRound after a delay.
	UFUNCTION()
	void CallStartNextRound();

	UPROPERTY()
	UEnemyWaveManagementSystem* EnemyWaveManager;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Weapon Upgrades
	
	/**
	 * @brief Increases given weapon's MaxChargeAmount by Amount.
	 * @param WeaponToUpgrade  WeaponBase child to be changed.
	 * @param Amount Amount added to give weapon's MaxChargeAmount.
	 */
	UFUNCTION(BlueprintCallable)
		void IncreaseMaxChargeAmount(AWeaponBase* WeaponToUpgrade, float Amount);

	/**
	* @brief Increases the given AWeaponBase's ShotDamage.
	* @param Amount Value added to WeaponToUpgrade's ShotDamage.
	*/
	UFUNCTION(BlueprintCallable)
		void IncreaseWeaponDamageByAmount(AWeaponBase* WeaponToUpgrade, float Amount);

	/**
	 * @brief Increases the given AWeaponBase's ChargeCooldownRate.
	 * @param Amount Value added to WeaponToUpgrade's ChargeCooldownRate.
	 */
	UFUNCTION(BlueprintCallable)
		void IncreaseChargeCooldownRate(AWeaponBase* WeaponToUpgrade, float Amount);

// Health Upgrades

	/**
	 * @brief Increases the given character's max health by a float amount.
	 * @param Amount Amount to be added to Character's Max Health.
	 */
	UFUNCTION(BlueprintCallable)
		void IncreaseMaxHealthByAmount(float Amount);
	
	/**
	 * @brief Increases the character's max health by a percentage.
	 * @param PercentageAmount Percentage of health to be added to Character's Max Health.
	 */
	UFUNCTION(BlueprintCallable)
		void IncreaseMaxHealthByPercentage(float PercentageAmount);

// Movement Upgrades

	/**
	 * @brief Increases the character's movement speed by Amount.
	 * @param Amount Value added to the Character's current move speed.
	 */
	UFUNCTION(BlueprintCallable)
		void IncreaseMovementSpeedByAmount(int Amount);
	
	/**
	 * @brief Sets the Player's max jump amount to 2.
	 */
	UFUNCTION(BlueprintCallable)
		void UnlockDoubleJump();

	/**
	 * @brief Decrease the Player's grapple cooldown by Amount.
	 * @param Seconds Value decreased from AWeaponBase's ChargeCooldownRate.
	 */
	UFUNCTION(BlueprintCallable)
		void DecreaseGrappleCooldownBySeconds(float Seconds);

// UI

	UFUNCTION(BlueprintCallable)
	void OpenUpgradeMenu();

	UFUNCTION(BlueprintCallable)
	void CloseUpgradeMenu();

	UPROPERTY(BlueprintReadOnly)
	bool bIsMenuOpen;

	//Button Images

	UPROPERTY()
	UTexture* MovementSpeedImage;

	UPROPERTY()
	UTexture* MaxHealthImage;

	UPROPERTY()
	UTexture* WeaponDamageImage;

	UPROPERTY()
	UTexture* ChargeCooldownImage;

	UPROPERTY()
	UTexture* GrappleCooldownImage;

	UPROPERTY()
	UTexture* DoubleJumpUpgradeImage;

	UPROPERTY()
	UTexture* MaxChargeImage;

// Upgrade Selection Functionality
	
	// Available upgrades for the player.
	UPROPERTY(EditAnywhere, Category = "AvailableUpgrades")
	TArray<FUpgradeChoice> UpgradeChoices =
		{
			// Health
			FUpgradeChoice(0, EUpgradeType::MaxHealth, 5, MaxHealthImage),
			FUpgradeChoice(1, EUpgradeType::MaxHealth, 5, MaxHealthImage),
			FUpgradeChoice(2, EUpgradeType::MaxHealth, 5, MaxHealthImage),
			FUpgradeChoice(3, EUpgradeType::MaxHealth, 5, MaxHealthImage),
			FUpgradeChoice(4, EUpgradeType::MaxHealth, 5, MaxHealthImage),
			// Weapon Damage (ToDo: Specific Weapon (Currently effects active weapon)
			FUpgradeChoice(5, EUpgradeType::WeaponDamage, 5, WeaponDamageImage),
			FUpgradeChoice(6, EUpgradeType::WeaponDamage, 5, WeaponDamageImage),
			FUpgradeChoice(7, EUpgradeType::WeaponDamage, 5, WeaponDamageImage),
			FUpgradeChoice(8, EUpgradeType::WeaponDamage, 5, WeaponDamageImage),
			FUpgradeChoice(9, EUpgradeType::WeaponDamage, 5, WeaponDamageImage),
			// Move Speed
			FUpgradeChoice(10, EUpgradeType::MovementSpeed, 5, MovementSpeedImage),
			FUpgradeChoice(11, EUpgradeType::MovementSpeed, 5, MovementSpeedImage),
			FUpgradeChoice(12, EUpgradeType::MovementSpeed, 5, MovementSpeedImage),
			// Double Jump
			FUpgradeChoice(13, EUpgradeType::UnlockDoubleJump, 0, DoubleJumpUpgradeImage),
			// Max Weapon Charge (ToDo: Specific Weapon (Currently effects active weapon)
			FUpgradeChoice(14, EUpgradeType::MaxChargeAmount, 5, MaxChargeImage),
			FUpgradeChoice(15, EUpgradeType::MaxChargeAmount, 5, MaxChargeImage),
			FUpgradeChoice(16, EUpgradeType::MaxChargeAmount, 5, MaxChargeImage),
			// Weapon Cooldown (ToDo: Specific Weapon (Currently effects active weapon)
			FUpgradeChoice(17, EUpgradeType::ChargeCooldown, 5, ChargeCooldownImage),
			FUpgradeChoice(18, EUpgradeType::ChargeCooldown, 5, ChargeCooldownImage),
			FUpgradeChoice(19, EUpgradeType::ChargeCooldown, 5, ChargeCooldownImage),
			// Grapple Cooldown
			FUpgradeChoice(20, EUpgradeType::GrappleCooldown, 1, GrappleCooldownImage),
			FUpgradeChoice(21, EUpgradeType::GrappleCooldown, 1, GrappleCooldownImage),
			FUpgradeChoice(22, EUpgradeType::GrappleCooldown, 1, GrappleCooldownImage),
			// ToDo: Ability Cooldown
			// ToDo: Grapple Range
			// ToDo: Dash Distance
			// ToDo: Crit Hit Multiplier
		};


	// Sets values of UpgradeChoice1/2/3 to be used by UpgradeChoice functions.
	void PrepareUpgradeChoices();

	/**
	 * @brief  Called through PrepareUpgradeChoices(), used to select from UpgradeChoices[].
	 * @return A copy of an FUpgradeChoice from  UpgradeChoices[]
	 */
	FUpgradeChoice GetUpgradeChoice();
	
	UPROPERTY();
	FUpgradeChoice UpgradeChoice1;

	UPROPERTY();
	FUpgradeChoice UpgradeChoice2;

	UPROPERTY();
	FUpgradeChoice UpgradeChoice3;

	/**
	 * @brief Applies UpgradeChoice1 to the player and removes it from UpgradeChoices[].
	 */
	UFUNCTION()
	void ApplyUpgrade1();

	/**
	 * @brief Applies UpgradeChoice2 to the player and removes it from UpgradeChoices[].
	 */
	UFUNCTION()
	void ApplyUpgrade2();

	/**
	 * @brief Applies UpgradeChoice3 to the player and removes it from UpgradeChoices[].
	 */
	UFUNCTION()
	void ApplyUpgrade3();

	/**
	 * @brief Removes first instance of FUpgradeChoice from UpgradeChoices[] with the given ID.
	 * @param ID Unique ID number of FUpgradeChoice to be removed.
	 */
	void RemoveUpgradeChoice(int ID);

	// Temporary function to return text before we have upgrade card art.
	FString GetUpgradeEnumValueText(int Value) const;
	
};
