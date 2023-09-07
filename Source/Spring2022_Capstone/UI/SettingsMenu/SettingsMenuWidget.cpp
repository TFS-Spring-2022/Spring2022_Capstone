// Created by Spring2022_Capstone team

#include "SettingsMenuWidget.h"
#include "Spring2022_Capstone/UI/MainMenu/MainMenuManager.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Slider.h"
#include "Spring2022_Capstone/CustomGameUserSettings.h"

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

	Settings = UCustomGameUserSettings::GetCustomGameUserSettings();

	if (Settings)
	{
		UE_LOG(LogTemp, Display, TEXT("GOT HERE"));
		YSensitivitySlider->SetValue(Settings->YSensitivity);
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
	UE_LOG(LogTemp, Display, TEXT("%f"), Value);
}

void USettingsMenuWidget::OnXSensitivityValueChanged(float Value)
{
	UE_LOG(LogTemp, Display, TEXT("%f"), Value);
}
