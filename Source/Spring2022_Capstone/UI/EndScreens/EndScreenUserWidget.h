// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Spring2022_Capstone/GameplaySystems/ScoreSystemManagerSubSystem.h"
#include "EndScreenUserWidget.generated.h"

class UPanelWidget;
class UImage;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS(Abstract)
class SPRING2022_CAPSTONE_API UEndScreenUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget* RootPanel;

	//BackgroundImage
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* BackgroundImage;

	// Title
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* VictoryText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ReturnToMainMenuButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ReturnToMainMenuText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ExitButtonText;
	
	// Score Counters
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HitsTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HeadshotsTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HitsWhileAirborneTextBlock; 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* EnemiesKilledTextBlock; 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* EnemiesKilledWithHazardsTextBlock; 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ElitesKilledTextBlock; 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SnipersDisabledTextBlock;

	// ToDo: Set Tool Tip Explanations
	// Accolades
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SkullNCrosshairTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CaptainOfWarTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SkyPirateTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LandLubberTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CloseCallCorsairTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* OpportunistTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CaptainsCoupTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DoubleAerialPlunderTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* BlunderBlastTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SkyBuccaneerTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HotHeadedTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NimbleBonesTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DeathDodgerTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PiratesFortitudeTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlunderersProwessTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* IPreferTreasureTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PirateBlitzTextBlock;

private: 

	UFUNCTION()
		void ReturnToMenuButtonPressed();

	UFUNCTION()
		void OnExitButtonPressed();

	/**
	 * @brief Takes EScoreCounters values from ScoreSystemManagerSubSystem and
	 * displays them in their respective text blocks.
	 */
	void SetScoreStatTextBoxes();

	/**
	 * @brief Takes EAccolade counts from ScoreSystemManagerSubSystem and
	 * displays them in their respective text blocks.
	 */
	void SetAccoladeTextBoxes();

	UPROPERTY()
	UScoreSystemManagerSubSystem* ScoreSystemManager;
	
};
