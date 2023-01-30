// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuHUD.h"
#include "SMainMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"

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
        GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));
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
