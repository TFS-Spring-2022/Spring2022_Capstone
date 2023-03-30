// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UPanelWidget;
class UProgressBar;
class UImage;

UCLASS(Abstract)
class SPRING2022_CAPSTONE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry &MyGeometry, float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *RootPanel;
	// Health bar
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar *HealthBar;
	// Crosshair
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage *Crosshair;
	// Grapple
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage *GrappleIcon;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar *GrappleCooldownBar;

private:
	UFUNCTION()
	void OnHealthChanged(float HealthValue);
	UFUNCTION()
	void OnGrappleTriggered(FTimerHandle &TimerHandle);
	float GrappleCooldown;

	FTimerHandle *GrappleTimerHandle;
};
