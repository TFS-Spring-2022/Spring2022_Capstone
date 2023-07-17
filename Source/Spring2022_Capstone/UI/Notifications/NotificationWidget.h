// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotificationWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API UNotificationWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget* RootPanel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* NotificationText;

public:
	
	UFUNCTION(BlueprintCallable)
	void ChangeNotificationText(FText NewText);
	
};
