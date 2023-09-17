// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBox.h"
#include "Components/ComboBoxString.h"
#include "SettingsMenuWidget.generated.h"

class UPanelWidget;
class UImage;
class UTextBlock;
class AMainMenuManager;
class UButton;
class USlider;
class UCustomGameUserSettings;
class APlayerCharacter;

UCLASS(Abstract)
class SPRING2022_CAPSTONE_API USettingsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:

	AMainMenuManager *Manager;
	UPROPERTY(BlueprintReadWrite)
	UCustomGameUserSettings *Settings;
	APlayerCharacter *Player;

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
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USlider *YSensitivitySlider;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USlider *XSensitivitySlider;

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
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UComboBoxString* WindowModeComboBox;
	UFUNCTION()
	void OnWindowModeSelected(FString SelectedOption, ESelectInfo::Type SelectInfo);

	// Reset Confirmation
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget* RestartPanel;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RestartConfirmButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RestartIgnoreButton;

	// Audio
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton *AudioButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget *AudioPanel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USlider *MasterVolumeSlider;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USlider *MusicSlider;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USlider *SFXSlider;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USlider *VoiceSlider;

	UPROPERTY(EditAnywhere)
	USoundClass* Master;
	UPROPERTY(EditAnywhere)
	USoundClass* SFX;
	UPROPERTY(EditAnywhere)
	USoundClass* Music;
	UPROPERTY(EditAnywhere)
	USoundClass* Voice;

	UPROPERTY(EditAnywhere)
	USoundMix* SBP_MasterVolume;
	UPROPERTY(EditAnywhere)
	USoundMix* SBP_SFXVolume;
	UPROPERTY(EditAnywhere)
	USoundMix* SBP_MusicVolume;
	UPROPERTY(EditAnywhere)
	USoundMix* SBP_VoiceVolume;
	
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

	UFUNCTION()
	void OnRestartConfirmButtonPressed();

	UFUNCTION()
	void RestartIgnoreButtonPressed();
	
	UFUNCTION()
	void OnYSensitivityValueChanged(float Value);
	UFUNCTION()
	void OnXSensitivityValueChanged(float Value);

	UFUNCTION()
	void OnMasterVolumeValueChanged(float Value);

	UFUNCTION()
	void OnSFXValueChanged(float Value);

	UFUNCTION()
	void OnMusicValueChanged(float Value);

	UFUNCTION()
	void OnVoiceValueChanged(float Value);
	
};
