// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsMenuWidget.generated.h"

class UPanelWidget;
class UImage;
class UTextBlock;
class AMainMenuManager;
class UButton;

UCLASS(Abstract)
class SPRING2022_CAPSTONE_API USettingsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:

	AMainMenuManager *Manager;

	// Root Panel
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *RootPanel;

	// Back Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton *BackButton;

	// BackgroundImage
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage *BackgroundImage;

	// General
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton *GeneralButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *GeneralPanel;

	// Controls
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton *ControlsButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *ControlsPanel;

	// Graphics
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton *GraphicsButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget *GraphicsPanel;

	// Audio
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton *AudioButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget *AudioPanel;

private:
	

	UFUNCTION()
	void OnBackButtonPressed();

	UFUNCTION()
	void OnGeneralButtonPressed();

	UFUNCTION()
	void OnControlsButtonPressed();

	UFUNCTION()
	void OnGraphicsButtonPressed();

	UFUNCTION()
	void OnAudioButtonPressed();

	UFUNCTION()
	void ClearPanels();
};
