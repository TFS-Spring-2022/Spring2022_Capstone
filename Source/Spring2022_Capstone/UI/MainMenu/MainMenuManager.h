// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Spring2022_Capstone/UI/BaseUIManager.h"
#include "MainMenuManager.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API AMainMenuManager : public ABaseUIManager
{
	GENERATED_BODY()
	
	

public:	
	
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> SettingsWidget;

	UFUNCTION()
	void DisplaySettingsWidget();
	UFUNCTION()
	void DismissSettingsWidget();

private:
	UUserWidget *_SettingsWidget;
};
