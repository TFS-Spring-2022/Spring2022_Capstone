// Created by Spring2022_Capstone team

#include "TitleScreenHUD.h"
#include "STitleScreenWidget.h"


void ATitleScreenHUD::BeginPlay()
{
    Super::BeginPlay();
    ShowMenu();
}

void ATitleScreenHUD::ShowMenu()
{
    if (GEngine && GEngine->GameViewport)
    {
        TitleScreenWidget = SNew(STitleScreenWidget).TitleScreenHUD(this);
        GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(TitleScreenContainer, SWeakWidget).PossiblyNullContent(TitleScreenWidget.ToSharedRef()), 0);
        if (PlayerOwner)
        {
            PlayerOwner->bShowMouseCursor = true;
        }
    }
}
