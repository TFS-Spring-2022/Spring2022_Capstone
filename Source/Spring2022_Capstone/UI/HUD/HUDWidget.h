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
	// Wave Timer
	UPROPERTY(EditAnywhere, meta = (BindWIdget))
	UTextBlock* WaveTimerTextBlock;
	// Health bar
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar *HealthBar;
	// Overheat Bar
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
	// Enemies Remaining Countdown
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* EnemiesRemainingTextBlock;
	// Blood Splatter Image
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* BloodSplatterImage;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* BloodSplatterAnimation;
	// HUD Fade In Animation
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HUDFadeInAnimation;

	void FadeInHUD();
	void FadeOutHUD();

	void HideWaveTimer();
	void ShowWaveTimer();
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* WaveTimerFadeInAnimation;

	// All black image for fading out player vision on death.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* FadeToBlackImage;
	// Black image fade in and stay animatino
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeToBlackAnim;

	void PlayFadeToBlackAnim();
	

	/**
	 * @brief Play the blood splatter animation from 'BloodSplatterAnimationTime'.
	 * @note This time is used to extend reverse timer and prevent blood splatter animation from
	 * replaying when taking additional damage.
	 */
	void PlayBloodSplatterAnimation();
	
	// Sets the EquippedWeaponIcon and StashedWeaponIcons to show the given Texture2Ds.
	void SetWeaponIcons(UTexture2D* EquippedWeaponTexture2D, UTexture2D* StashedWeaponTexture2D) const;

	/**
	 * @brief Displays the time elapsed in the current wave.
	 * @note Called from EnemyWaveManagementSystem::ConvertElapsedTime;
	 */
	void SetWaveTimerText(int Minutes, float Seconds);

	/**
	 * @brief Set's the text box to display the remaining enemies in the current wave.
	 * @param NumberOfEnemies Number of enemies remaining in the current wave.
	 */
	void SetEnemiesRemainingText(int NumberOfEnemies);
	
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

	/**
	 * @brief Reverse blood splatter animation to fade out image.
	 */
	UFUNCTION()
	void PlayerBloodSplatterBackwards();

	// Timer used to call blood splatter fade out.
	FTimerHandle BloodSplatterReverseTimerHandle;
	// Time before blood splatter fade out is played.
	const float TIME_BEFORE_BLOOD_SPLATTER_FADE_OUT = 1.0f;
	/**
	 * @brief Current time of the playing blood splatter animation.
	 * @note Used to extend blood splatter animation when taking multiple hits.
	 */
	float BloodSplatterAnimationTime;
	
};
