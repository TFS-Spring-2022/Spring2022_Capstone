// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UPanelWidget;
class UImage;
class UTextBlock;
class UButton;

UCLASS(Abstract)
class SPRING2022_CAPSTONE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *RootWidget;
	//BackgroundImage
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* BackgroundImage;
	// Title
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TitleText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	// Play Button
	UButton* PlayButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayButtonText;
	// Exit Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ExitButtonText;
};
