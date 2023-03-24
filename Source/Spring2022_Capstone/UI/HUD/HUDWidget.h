// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UPanelWidget;
class UProgressBar;

UCLASS()
class SPRING2022_CAPSTONE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *RootPanel;
	// Health bar
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar *HealthBar;

private:
	UPROPERTY()
	void OnHeathChanged();
};
