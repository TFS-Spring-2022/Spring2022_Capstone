// Created by Spring2022_Capstone team

#include "EndScreenUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UEndScreenUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReturnToMainMenuButton->OnClicked.AddUniqueDynamic(this, &UEndScreenUserWidget::ReturnToMenuButtonPressed);
	ExitButton->OnClicked.AddUniqueDynamic(this, &UEndScreenUserWidget::OnExitButtonPressed);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
}

void UEndScreenUserWidget::ReturnToMenuButtonPressed()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}


void UEndScreenUserWidget::OnExitButtonPressed()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
