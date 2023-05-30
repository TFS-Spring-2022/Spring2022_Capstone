// Created by Spring2022_Capstone team

#include "SettingsMenuWidget.h"
#include "Spring2022_Capstone/UI/MainMenu/MainMenuManager.h"
#include "Components/Button.h"

void USettingsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	BackButton->OnClicked.AddUniqueDynamic(this, &USettingsMenuWidget::OnBackButtonPressed);
	GeneralButton->OnClicked.AddUniqueDynamic(this, &USettingsMenuWidget::OnGeneralButtonPressed);
	GraphicsButton->OnClicked.AddUniqueDynamic(this, &USettingsMenuWidget::OnGraphicsButtonPressed);
	AudioButton->OnClicked.AddUniqueDynamic(this, &USettingsMenuWidget::OnAudioButtonPressed);
	ControlsButton->OnClicked.AddUniqueDynamic(this, &USettingsMenuWidget::OnControlsButtonPressed);
}

void USettingsMenuWidget::OnBackButtonPressed()
{
    Manager->DismissSettingsWidget();
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
