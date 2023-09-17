// Created by Spring2022_Capstone team

#include "SettingsMenuWidget.h"
#include "Spring2022_Capstone/UI/MainMenu/MainMenuManager.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Slider.h"
#include "Spring2022_Capstone/CustomGameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

void USettingsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BackButton->OnClicked.AddUniqueDynamic(this, &USettingsMenuWidget::OnBackButtonPressed);
	GeneralButton->OnClicked.AddUniqueDynamic(this, &USettingsMenuWidget::OnGeneralButtonPressed);
	GraphicsButton->OnClicked.AddUniqueDynamic(this, &USettingsMenuWidget::OnGraphicsButtonPressed);
	AudioButton->OnClicked.AddUniqueDynamic(this, &USettingsMenuWidget::OnAudioButtonPressed);
	ControlsButton->OnClicked.AddUniqueDynamic(this, &USettingsMenuWidget::OnControlsButtonPressed);
	RestartConfirmButton->OnClicked.AddUniqueDynamic(this, &USettingsMenuWidget::OnRestartConfirmButtonPressed);
	RestartIgnoreButton->OnClicked.AddUniqueDynamic(this, &USettingsMenuWidget::RestartIgnoreButtonPressed);
	WindowModeComboBox->AddOption("Full Screen");
	WindowModeComboBox->AddOption("Borderless Full Screen");
	WindowModeComboBox->AddOption("Windowed");
	WindowModeComboBox->OnSelectionChanged.AddDynamic(this, &USettingsMenuWidget::OnWindowModeSelected);

	YSensitivitySlider->OnValueChanged.AddUniqueDynamic(this, &USettingsMenuWidget::OnYSensitivityValueChanged);
	XSensitivitySlider->OnValueChanged.AddUniqueDynamic(this, &USettingsMenuWidget::OnXSensitivityValueChanged);

	MasterVolumeSlider->OnValueChanged.AddUniqueDynamic(this, &USettingsMenuWidget::OnMasterVolumeValueChanged);
	SFXSlider->OnValueChanged.AddUniqueDynamic(this, &USettingsMenuWidget::OnSFXValueChanged);
	MusicSlider->OnValueChanged.AddUniqueDynamic(this, &USettingsMenuWidget::OnMusicValueChanged);
	VoiceSlider->OnValueChanged.AddUniqueDynamic(this, &USettingsMenuWidget::OnVoiceValueChanged);

	Settings = UCustomGameUserSettings::GetCustomGameUserSettings();
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Settings)
	{
		YSensitivitySlider->SetValue(Settings->YSensitivity);
		XSensitivitySlider->SetValue(Settings->XSensitivity);

		
		MasterVolumeSlider->SetValue(Settings->MasterVolumeValue);
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),SBP_MasterVolume,Master,Settings->MasterVolumeValue,1,0,true);
		UGameplayStatics::PushSoundMixModifier(GetWorld(),SBP_MasterVolume);
		
		SFXSlider->SetValue(Settings->SFXVolumeValue);
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),SBP_SFXVolume,SFX,Settings->SFXVolumeValue,1,0,true);
		UGameplayStatics::PushSoundMixModifier(GetWorld(),SBP_SFXVolume);
		
		MusicSlider->SetValue(Settings->MusicVolumeValue);
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),SBP_MusicVolume,Music,Settings->MusicVolumeValue,1,0,true);
		UGameplayStatics::PushSoundMixModifier(GetWorld(),SBP_MusicVolume);
		
		VoiceSlider->SetValue(Settings->VoiceVolumeValue);
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),SBP_VoiceVolume,Voice,Settings->VoiceVolumeValue,1,0,true);
		UGameplayStatics::PushSoundMixModifier(GetWorld(),SBP_VoiceVolume);
	}
}

void USettingsMenuWidget::OnWindowModeSelected(FString SelectedOption, ESelectInfo::Type SelectInfo)
{
	UGameUserSettings *GameUserSettings = GEngine->GetGameUserSettings();
	if (!GameUserSettings)
		return;

	if (SelectedOption == "Full Screen")
	{
		GameUserSettings->SetScreenResolution(GameUserSettings->GetDesktopResolution());
		GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	}
	else if (SelectedOption == "Borderless Full Screen")
	{
		GameUserSettings->SetScreenResolution(GameUserSettings->GetDesktopResolution());
		GameUserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	}
	else if (SelectedOption == "Windowed")
	{
		GameUserSettings->SetScreenResolution(FIntPoint(1280, 720));
		GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
	}
	RestartPanel->SetVisibility(ESlateVisibility::Visible);
}

void USettingsMenuWidget::OnBackButtonPressed()
{
	if (Manager)
		Manager->DismissSettingsWidget();
	else
		SetVisibility(ESlateVisibility::Hidden);
}

void USettingsMenuWidget::OnGeneralButtonPressed()
{
	ClearPanels();
	GeneralPanel->SetVisibility(ESlateVisibility::Visible);
}

void USettingsMenuWidget::OnControlsButtonPressed()
{
	ClearPanels();
	ControlsPanel->SetVisibility(ESlateVisibility::Visible);
}

void USettingsMenuWidget::OnGraphicsButtonPressed()
{
	ClearPanels();
	GraphicsPanel->SetVisibility(ESlateVisibility::Visible);
}

void USettingsMenuWidget::OnAudioButtonPressed()
{
	ClearPanels();
	AudioPanel->SetVisibility(ESlateVisibility::Visible);
}

void USettingsMenuWidget::ClearPanels()
{
	GeneralPanel->SetVisibility(ESlateVisibility::Hidden);
	GraphicsPanel->SetVisibility(ESlateVisibility::Hidden);
	ControlsPanel->SetVisibility(ESlateVisibility::Hidden);
	AudioPanel->SetVisibility(ESlateVisibility::Hidden);
}

void USettingsMenuWidget::OnRestartConfirmButtonPressed()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

void USettingsMenuWidget::RestartIgnoreButtonPressed()
{
	RestartPanel->SetVisibility(ESlateVisibility::Hidden);
}

void USettingsMenuWidget::OnYSensitivityValueChanged(float Value)
{
	Settings->YSensitivity = Value;
	if (Player)
		Player->SetYSensitivity(Value);
}

void USettingsMenuWidget::OnXSensitivityValueChanged(float Value)
{
	Settings->XSensitivity = Value;
	if (Player)
		Player->SetXSensitivity(Value);
}

void USettingsMenuWidget::OnMasterVolumeValueChanged(float Value)
{
	Settings->MasterVolumeValue = Value;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(),SBP_MasterVolume,Master,Value,1,0,true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(),SBP_MasterVolume);
}

void USettingsMenuWidget::OnSFXValueChanged(float Value)
{
	Settings->SFXVolumeValue = Value;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(),SBP_SFXVolume,SFX,Value,1,0,true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(),SBP_SFXVolume);
}

void USettingsMenuWidget::OnMusicValueChanged(float Value)
{
	Settings->MusicVolumeValue = Value;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(),SBP_MusicVolume,Music,Value,1,0,true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(),SBP_MusicVolume);
}

void USettingsMenuWidget::OnVoiceValueChanged(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,"Voice volume set");
	Settings->VoiceVolumeValue = Value;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(),SBP_VoiceVolume,Voice,Value,1,0,true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(),SBP_VoiceVolume);
}

