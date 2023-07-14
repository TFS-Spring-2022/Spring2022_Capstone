// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UPanelWidget;
class UProgressBar;
class UImage;
class UTextBlock;

UCLASS(Abstract)
class SPRING2022_CAPSTONE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry &MyGeometry, float DeltaTime) override;

public:


	void PlayCrosshairAnimation();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *RootPanel;
	// Health bar
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar *HealthBar;
	// Crosshair
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage *Crosshair;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage *HitCrosshair;
	
	UPROPERTY(BlueprintReadWrite)
		class UWidgetAnimation* CrosshairAnimation;

	// Grapple
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage *GrappleIcon;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar *GrappleCooldownBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UProgressBar * OverheatBar;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock *GrappleCooldownText;

	class APlayerCharacter* PlayerRef;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Grapple")
	float GrappleCooldown;
	
	UFUNCTION()
	void OnHealthChanged(float HealthValue);
	UFUNCTION()
	void OnGrappleActivated();
	UFUNCTION()
	void OnGrappleCooldownStart(FTimerHandle &TimerHandle);
	UFUNCTION()
	void OnGrappleCooldownEnd();
	

	int MaxHealth;

	FTimerHandle *GrappleTimerHandle;
};
