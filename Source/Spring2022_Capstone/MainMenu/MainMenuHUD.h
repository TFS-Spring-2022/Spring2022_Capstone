// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 *
 */
UCLASS()
class SPRING2022_CAPSTONE_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	TSharedPtr<class SMainMenuWidget> MenuWidget;
	TSharedPtr<class SConfirmationWidget> ConfirmationWidget;
	TSharedPtr<class SWidget> MenuWidgetContainer;
	TSharedPtr<class SWidget> ConfirmationWidgetContainer;

	virtual void BeginPlay() override;

public: 

	void ShowMenu();
	void RemoveMenu();
	void ShowQuitConfirmation();
	void RemoveQuitConfirmation();
	void ExitGame();
};