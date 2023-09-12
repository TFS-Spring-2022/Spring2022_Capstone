// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "WaveAnnouncerWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API UWaveAnnouncerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* AnnouncementTextBlock;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnnounceWidgetAnim;

	// Time of the AnnounceWidgetAnim when it is paused. Used when un-pausing.
	float AnnounceAnimPauseTime;
	
public:

	void SetAnnouncementTextBlock(FText Announcement);

	/**
	 * @brief Pauses/Resumes announcement animation
	 * @param bIsPaused True - Pause the animation, False - Resume.
	 */
	void PauseAnnouncementAnimation(bool bIsPaused);
};
