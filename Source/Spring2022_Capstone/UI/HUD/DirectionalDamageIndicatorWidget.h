// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "DirectionalDamageIndicatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API UDirectionalDamageIndicatorWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UPanelWidget* RootPanel;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* DamageIndicator;

	UPROPERTY()
	APlayerCharacter* Player;
	
	
};
