// Created by Spring2022_Capstone team

#include "VictoryScreenUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UVictoryScreenUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReturnToMainMenuButton->OnClicked.AddUniqueDynamic(this, &UVictoryScreenUserWidget::ReturnToMenuButtonPressed);
	ExitButton->OnClicked.AddUniqueDynamic(this, &UVictoryScreenUserWidget::OnExitButtonPressed);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
}

void UVictoryScreenUserWidget::ReturnToMenuButtonPressed()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}


void UVictoryScreenUserWidget::OnExitButtonPressed()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
