// Created by Spring2022_Capstone team


#include "NotificationWidget.h"
#include "Components/TextBlock.h"

void UNotificationWidget::ChangeNotificationText(FText NewText)
{
	if(NotificationText)
		NotificationText->SetText(NewText);
}
