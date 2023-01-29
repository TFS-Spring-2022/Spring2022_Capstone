// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuHUD.h"
#include "SMainMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"

void AMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("HERE"));
    if (GEngine && GEngine->GameViewport)
    {
        UE_LOG(LogTemp, Display, TEXT("HERE1"));
        MenuWidget = SNew(SMainMenuWidget).MenuHUD(this);
        GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));
    }
}


// // Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.   
// #include "SlateTutorials.h" 
// #include "MainMenuHUD.h" 
// #include "MainMenuUI.h" 
// #include "Engine.h"   
// void AMainMenuHUD::PostInitializeComponents() { Super::PostInitializeComponents();   SAssignNew(MainMenuUI, SMainMenuUI).MainMenuHUD(this);   if (GEngine->IsValidLowLevel()) { GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MainMenuUI.ToSharedRef())); } }