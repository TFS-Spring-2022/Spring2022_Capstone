// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
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
	virtual void NativeTick(const FGeometry &MyGeometry, float DeltaTime) override;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UPanelWidget* RootPanel;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* DamageIndicatorImage;

	UPROPERTY()
	class APlayerCharacter* Player;

	UPROPERTY()
	AActor* DamagingActor;

public:

	void SetDamagingActor(AActor* Damager);

private:

	// Begins indicator image fade in process and starts timer for fade out process.
	void StartNotification();

	// Begins indicator image fade out process and clears DamagingActor reference
	UFUNCTION()
	void HideNotification();
	
	// Timer used for indicator image visibility
	FTimerHandle NotificationVisibilityTimerHandle;

	// Time notification is visible in seconds
	UPROPERTY(EditAnywhere, Category = "Damage Indicator")
	float VisibilityTime;
	
	bool bFadingIn;
	bool bFadingOut;

	float const NOTIFICATION_FADEOUT_SPEED = 5.0f;
	float const NOTIFICATION_FADEIN_SPEED = 10.0f;
	
};
