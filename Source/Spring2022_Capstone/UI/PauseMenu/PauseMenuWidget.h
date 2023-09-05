// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Spring2022_Capstone/UI/SettingsMenu/SettingsMenuWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

protected:
	
	// Root Panel
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *RootPanel;

	// MainMenu Panel
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *PauseMenuPanel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ResumeButton;

	UFUNCTION()
	void OnResumeButtonPressed();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* SettingsButton;

	UFUNCTION()
	void OnSettingsButtonPressed();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ReturnToMainMenuButton;

	UFUNCTION()
	void OnReturnToMainMenuButtonPressed();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ExitGameButton;

	UFUNCTION()
	void OnExitGameButtonPressed();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USettingsMenuWidget* SettingsMenuWidget;

private:

	UPROPERTY()
	class APlayerCharacter* Player;

public:
	/**
	 * @brief Used to hide the pause menu if the player exits via the pause
	* button while inside the settings menu.
	 */
	void HideSettingsMenu();
	
};
