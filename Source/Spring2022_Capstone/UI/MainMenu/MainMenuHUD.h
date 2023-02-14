// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class SConfirmationWidget;
class SMainMenuWidget;

UCLASS()
class SPRING2022_CAPSTONE_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	TSharedPtr<SMainMenuWidget> MenuWidget;
	TSharedPtr<SConfirmationWidget> ConfirmationWidget;
	TSharedPtr<SWidget> MenuWidgetContainer;
	TSharedPtr<SWidget> ConfirmationWidgetContainer;

	virtual void BeginPlay() override;

public: 

	void ShowMenu();
	void RemoveMenu();
	void ShowQuitConfirmation();
	void RemoveQuitConfirmation();
	void ExitGame();
};