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
	AActor* DamagingActor; // ToDo: Replace AActor reference with FVector location

public:

	void SetDamagingActor(AActor* Damager);

	UFUNCTION()
	void HideNotification();

	//private:

	// Makes DirectionalDamageIndicator visible and starts timer to hide again (ToDo: Fade?)
	void StartNotification();

	FTimerHandle NotificationVisibilityTimerHandle;

	// Time notification is visible in seconds
	UPROPERTY(EditAnywhere, Category = "Damage Indicator")
	float VisibilityTime;
	
};
