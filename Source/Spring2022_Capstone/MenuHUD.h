// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

/**
 *
 */
UCLASS()
class SPRING2022_CAPSTONE_API AMenuHUD : public AHUD
{
	GENERATED_BODY()
	// virtual void PostInitializeComponents() override;

protected:
	TSharedPtr<class SMainMenuWidget> MenuWidget;
	TSharedPtr<class SWidget> MenuWidgetContainer;

	virtual void BeginPlay() override;
};

// // Copyright 1998-2015 Epic Games, Inc. All Rights Reserved. // MainMenuHUD.h – Provides an implementation of the HUD that will embed the Main Menu Slate UI.
// #pragma once
// #include "GameFramework/HUD.h" #include "MainMenuHUD.generated.h" /** * Provides an implementation of the game’s Main Menu HUD, which will embed and respond to events triggered * within SMainMenuUI. */
// UCLASS()
// class SLATETUTORIALS_API AMainMenuHUD : public AHUD
// {
// 	GENERATED_BODY()
// 	// Initializes the Slate UI and adds it as widget content to the game viewport.
// 	virtual void PostInitializeComponents() override;
// 	// Reference to the Main Menu Slate UI.
// 	TSharedPtr<class SMainMenuUI> MainMenuUI;

// public:
// 	// Called by SMainMenu whenever the Play Game! button has been clicked.
// 	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Main Menu")
// 	void PlayGameClicked();
// 	// Called by SMainMenu whenever the Quit Game button has been clicked.
// 	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Main Menu")
// 	void QuitGameClicked();
// };