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

	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* AnnouncementTextBlock;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnnounceWidgetAnim;

	// Same as above animation but does not fade out.
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* VictoryWidgetAnim;

	// Time of the AnnounceWidgetAnim when it is paused. Used when un-pausing.
	float AnnounceAnimPauseTime;
	
public:

	void SetAnnouncementTextBlock(FText Announcement, bool bIsVictoryAnnouncement = false);

	/**
	 * @brief Pauses/Resumes announcement animation
	 * @param bIsPaused True - Pause the animation, False - Resume.
	 */
	void PauseAnnouncementAnimation(bool bIsPaused);

	void SetVictoryTextBlock(FText Announcement);
};
