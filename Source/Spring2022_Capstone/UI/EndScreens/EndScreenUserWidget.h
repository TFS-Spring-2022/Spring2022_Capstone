// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

	// Displays EScoreCounters value
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ScoreStatsTextBox;

private: 

	UFUNCTION()
		void ReturnToMenuButtonPressed();

	UFUNCTION()
		void OnExitButtonPressed();
};
