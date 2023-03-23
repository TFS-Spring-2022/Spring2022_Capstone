// Created by Spring2022_Capstone team

#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnPlayButtonPressed);
	ExitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnExitButtonPressed);
	YesButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnYesButtonPressed);
    NoButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnNoButtonPressed);
	// ConfirmationWidget->InitButtons();
}

void UMainMenuWidget::OnPlayButtonPressed()
{
	UGameplayStatics::OpenLevel(this, "Level");
}

void UMainMenuWidget::OnExitButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("TEST"));
	ExitConfirmationPanel->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuWidget::OnYesButtonPressed()
{
    UE_LOG(LogTemp, Display, TEXT("YES"));
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

void UMainMenuWidget::OnNoButtonPressed()
{
    UE_LOG(LogTemp, Display, TEXT("NO"));
    ExitConfirmationPanel->SetVisibility(ESlateVisibility::Hidden);
}
