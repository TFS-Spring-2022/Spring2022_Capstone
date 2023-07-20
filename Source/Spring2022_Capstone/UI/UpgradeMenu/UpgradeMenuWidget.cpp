// Created by Spring2022_Capstone team


#include "UpgradeMenuWidget.h"

void UUpgradeMenuWidget::SetUpgradeTextBox(int UpgradeChoiceNumber, FText UpgradeText)
{
	switch (UpgradeChoiceNumber)
	{
	case 1:
		Upgrade1Text->SetText(UpgradeText);
		break;
	case 2:
		Upgrade2Text->SetText(UpgradeText);
		break;
	case 3:
		Upgrade3Text->SetText(UpgradeText);
		break;
	default:
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Error - Upgrade box to update doesn't exist");
		break;
	}
}

void UUpgradeMenuWidget::SetUpgradeTextBoxVisibility(int UpgradeChoiceNumber, ESlateVisibility NewVisibility)
{
	switch (UpgradeChoiceNumber)
	{
	case 1:
		Upgrade1Text->SetVisibility(NewVisibility);
		break;
	case 2:
		Upgrade2Text->SetVisibility(NewVisibility);
		break;
	case 3:
		Upgrade3Text->SetVisibility(NewVisibility);
		break;
	default:
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Error - Upgrade Text to update doesn't exist");
		break;
	}
}
