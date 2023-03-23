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

	APlayerController *PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
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
