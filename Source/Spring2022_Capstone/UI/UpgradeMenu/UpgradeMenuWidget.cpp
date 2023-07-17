// Created by Spring2022_Capstone team


#include "UpgradeMenuWidget.h"

void UUpgradeMenuWidget::UpdateUpdateTextBox(int UpgradeChoiceNumber, FText UpgradeText)
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
