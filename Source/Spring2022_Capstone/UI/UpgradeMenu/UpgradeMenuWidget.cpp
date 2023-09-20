// Created by Spring2022_Capstone team


#include "UpgradeMenuWidget.h"

#include "Components/Image.h"

void UUpgradeMenuWidget::SetUpgradeTextBox(int UpgradeChoiceNumber, FText UpgradeText, UTexture* Image)
{
	switch (UpgradeChoiceNumber)
	{
	case 1:
		Upgrade1Text->SetText(UpgradeText);
		Upgrade1Button->WidgetStyle.Normal.SetResourceObject(Image);
		Upgrade1Button->WidgetStyle.Hovered.SetResourceObject(Image);
		Upgrade1Button->WidgetStyle.Pressed.SetResourceObject(Image);
		Upgrade1Button->WidgetStyle.Disabled.SetResourceObject(Image);
		break;
	case 2:
		Upgrade2Text->SetText(UpgradeText);
		Upgrade2Button->WidgetStyle.Normal.SetResourceObject(Image);
		Upgrade2Button->WidgetStyle.Hovered.SetResourceObject(Image);
		Upgrade2Button->WidgetStyle.Pressed.SetResourceObject(Image);
		Upgrade2Button->WidgetStyle.Disabled.SetResourceObject(Image);
		break;
	case 3:
		Upgrade3Text->SetText(UpgradeText);
		Upgrade3Button->WidgetStyle.Normal.SetResourceObject(Image);
		Upgrade3Button->WidgetStyle.Hovered.SetResourceObject(Image);
		Upgrade3Button->WidgetStyle.Pressed.SetResourceObject(Image);
		Upgrade3Button->WidgetStyle.Disabled.SetResourceObject(Image);
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
