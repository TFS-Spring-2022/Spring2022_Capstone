// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UPanelWidget;
class UProgressBar;
class UImage;
class UTextBlock;
class APlayerCharacter;

UCLASS(Abstract)
class SPRING2022_CAPSTONE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry &MyGeometry, float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere)
	APlayerCharacter* PlayerCharacter;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget *RootPanel;
	UPROPERTY(EditAnywhere, meta = (BindWIdget))
	UTextBlock* WaveTimerTextBlock;
	// Health bar
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar *HealthBar;
	// Overheat Barrie
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* OverheatBar;
	// Crosshair
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage *Crosshair;
	// Hit Marker
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* HitMarker;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HitMarkerAnimation;
	// Grapple
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage *GrappleIcon;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar *GrappleCooldownBar;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock *GrappleCooldownText;
	// Weapon Icons
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* EquippedWeaponIcon;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* StashedWeaponIcon;

	// Sets the EquippedWeaponIcon and StashedWeaponIcons to show the given Texture2Ds.
	void SetWeaponIcons(UTexture2D* EquippedWeaponTexture2D, UTexture2D* StashedWeaponTexture2D) const;

	/**
	 * @brief Displays the time elapsed in the current wave.
	 * @note Called from EnemyWaveManagementSystem::ConvertElapsedTime;
	 */
	void SetWaveTimerText(int Minutes, float Seconds);
	
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

	void PlayHitMarkerAnimation();

	// Temporary function to set weapon icons from NativeConstruct() after a delay.
	// ToDo: Replace when finalize weapon selection/spawning.
	UFUNCTION()
	void SetWeaponIconFromCharacter() const;

};
