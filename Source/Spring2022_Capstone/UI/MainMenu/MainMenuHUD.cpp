// Created by Spring2022_Capstone team

#include "MainMenuHUD.h"
#include "SMainMenuWidget.h"
#include "Spring2022_Capstone/UI/Misc/SConfirmationWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"

void AMainMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    ShowMenu();
}

void AMainMenuHUD::ShowMenu()
{
    if (GEngine && GEngine->GameViewport)
    {
        MenuWidget = SNew(SMainMenuWidget).MenuHUD(this);
        GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()), 0);
        if (PlayerOwner)
        {
            PlayerOwner->bShowMouseCursor = true;
            PlayerOwner->SetInputMode(FInputModeUIOnly());
        }
    }
}

void AMainMenuHUD::RemoveMenu()
{
    if (GEngine && GEngine->GameViewport && MenuWidgetContainer.IsValid())
    {
        GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());
    }
}

void AMainMenuHUD::ShowQuitConfirmation()
{
    if (GEngine && GEngine->GameViewport)
    {
        ConfirmationWidget = SNew(SConfirmationWidget).MenuHUD(this);
        GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(ConfirmationWidgetContainer, SWeakWidget).PossiblyNullContent(ConfirmationWidget.ToSharedRef()), 1);
    }
}

void AMainMenuHUD::RemoveQuitConfirmation()
{
    if (GEngine && GEngine->GameViewport && ConfirmationWidgetContainer.IsValid())
    {
        GEngine->GameViewport->RemoveViewportWidgetContent(ConfirmationWidgetContainer.ToSharedRef());
    }
}

void AMainMenuHUD::ExitGame()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
