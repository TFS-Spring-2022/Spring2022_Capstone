// Created by Spring2022_Capstone team
#include "MainMenuManager.h"
#include "Spring2022_Capstone/UI/SettingsMenu/SettingsMenuWidget.h"


void AMainMenuManager::DisplaySettingsWidget()
{
    if (SettingsWidget)
    {
        _SettingsWidget = CreateWidget(GetWorld(), SettingsWidget);

        if (USettingsMenuWidget *Widget = Cast<USettingsMenuWidget>(_SettingsWidget))
        {
            Widget->Manager = this;
        }

        _SettingsWidget->AddToViewport(2);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Type not specizfied for Settings Widget"));
    }
}

void AMainMenuManager::DismissSettingsWidget()
{
    _SettingsWidget->RemoveFromParent();
}