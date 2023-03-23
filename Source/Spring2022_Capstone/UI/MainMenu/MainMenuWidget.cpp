// Created by Spring2022_Capstone team

#include "MainMenuWidget.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (PlayButton)
	{
		PlayButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::PlayButtonPressed);
	}
}

void UMainMenuWidget::PlayButtonPressed()
{
	UGameplayStatics::OpenLevel(this, "Level");
}
