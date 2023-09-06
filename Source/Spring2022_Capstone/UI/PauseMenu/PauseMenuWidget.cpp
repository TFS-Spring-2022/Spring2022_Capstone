// Created by Spring2022_Capstone team


#include "PauseMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnResumeButtonPressed);
	SettingsButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnSettingsButtonPressed);
	ReturnToMainMenuButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnReturnToMainMenuButtonPressed);
	ExitGameButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnExitGameButtonPressed);

	SettingsMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UPauseMenuWidget::OnResumeButtonPressed()
{
	if(Player)
		Player->UnPause();
}

void UPauseMenuWidget::OnSettingsButtonPressed()
{
	if(!SettingsMenuWidget)
		return;

	// The settings menu widget is set on a higher Z-Order so the others do not need to be hidden.
	SettingsMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

void UPauseMenuWidget::OnReturnToMainMenuButtonPressed()
{
	// ToDo: Confirmation Buttons
	UGameplayStatics::OpenLevel(this, "MainMenu");
}

void UPauseMenuWidget::OnExitGameButtonPressed()
{
	// ToDo: Confirmation Buttons
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

void UPauseMenuWidget::HideSettingsMenu()
{
	if(SettingsMenuWidget)
		SettingsMenuWidget->SetVisibility(ESlateVisibility::Hidden);
}
