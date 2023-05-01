// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UPanelWidget;
class UImage;
class UTextBlock;
class UButton;
class UExitConfirmationWidget;

UCLASS(Abstract)
class SPRING2022_CAPSTONE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	//Root Panel
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *RootPanel;

	//BackgroundImage
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* BackgroundImage;

	//MainMenu Panel
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *MainMenuPanel;

	// Title
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TitleText;
	

	//Settings Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SettingsButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SettingsButtonText;

	// Play Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* PlayButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayButtonText;

	// Exit Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ExitButtonText;

	// Exit Confirmation
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *ExitConfirmationPanel;

	//BackgroundImage
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ExitConfirmationBackgroundImage;

	// Title
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ExitConfirmationTitleText;
	
	// Yes Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* YesButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* YesButtonText;

	// Exit Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* NoButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NoButtonText;

private:
	UFUNCTION()
	void OnPlayButtonPressed();

	UFUNCTION()
	void OnExitButtonPressed();

	UFUNCTION()
	void OnSettingButtonPressed();

	UFUNCTION()
	void OnYesButtonPressed();
	
	UFUNCTION()
	void OnNoButtonPressed();
};
