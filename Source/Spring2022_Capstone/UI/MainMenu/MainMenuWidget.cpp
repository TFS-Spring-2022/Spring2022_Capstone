// Created by Spring2022_Capstone team


#include "MainMenuWidget.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (TitleText)
	{
		TitleText->SetText(FText::FromString(TEXT("Hello world!")));
	}
}
