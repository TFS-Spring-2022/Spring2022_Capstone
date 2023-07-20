// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UpgradeMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API UUpgradeMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget* RootPanel;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Upgrade1Button;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Upgrade1Text;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Upgrade2Button;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Upgrade2Text;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Upgrade3Button;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Upgrade3Text;

public:

	// Changes text above given upgrade choice.
	void SetUpgradeTextBox(int UpgradeChoiceNumber, FText UpgradeText);

	FORCEINLINE UButton* GetUpgrade1Button() {return Upgrade1Button;}
	FORCEINLINE UButton* GetUpgrade2Button() {return Upgrade2Button;}
	FORCEINLINE UButton* GetUpgrade3Button() {return Upgrade3Button;}
	
};
