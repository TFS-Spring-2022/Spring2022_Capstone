// Created by Spring2022_Capstone team

#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/AudioComponent.h"
#include "Spring2022_Capstone/GameplaySystems/ScoreSystemManagerSubSystem.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnPlayButtonPressed);
	SettingsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnSettingButtonPressed);
	ExitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnExitButtonPressed);
	YesButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnYesButtonPressed);
	NoButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnNoButtonPressed);

	APlayerController *PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC, this);
	}
	GetGameInstance()->GetSubsystem<UScoreSystemManagerSubSystem>()->ResetScoreSystem();
	GetGameInstance()->GetSubsystem<USoundManagerSubSystem>()->PlaysMusic(GetGameInstance()->GetSubsystem<USoundManagerSubSystem>()->MainMenuMusicSC);
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red, "Menu SOunds");
}

void UMainMenuWidget::OnPlayButtonPressed()
{
	APlayerController *PC = GetWorld()->GetFirstPlayerController();
	
	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->bEnableClickEvents = false;
		PC->bEnableMouseOverEvents = false;
	}
	UGameplayStatics::OpenLevel(this, "PirateIsland");
}

void UMainMenuWidget::OnSettingButtonPressed()
{
	if(Manager)
	{
		Manager->DisplaySettingsWidget();
	}
}


void UMainMenuWidget::OnExitButtonPressed()
{
	ExitConfirmationPanel->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuWidget::OnYesButtonPressed()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

void UMainMenuWidget::OnNoButtonPressed()
{
	ExitConfirmationPanel->SetVisibility(ESlateVisibility::Hidden);
}
