// Created by Spring2022_Capstone team


#include "WaveAnnouncerWidget.h"

#include "Animation/UMGSequencePlayer.h"

void UWaveAnnouncerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Stop AnnouncementTextBlock from blocking mouse input.
	AnnouncementTextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UWaveAnnouncerWidget::SetAnnouncementTextBlock(FText Announcement, bool bIsVictoryAnnouncement)
{
	if(!AnnouncementTextBlock)
		return;

	AnnouncementTextBlock->SetText(Announcement);
	if(!bIsVictoryAnnouncement)
		PlayAnimation(VictoryWidgetAnim, 0, 1, EUMGSequencePlayMode::Forward, 1, true);
	else
		PlayAnimation(AnnounceWidgetAnim, 0, 1, EUMGSequencePlayMode::Forward, 1, true);
}

void UWaveAnnouncerWidget::PauseAnnouncementAnimation(bool bIsPaused)
{
	
	if(bIsPaused)
	{
		// Save current animation time to use when resuming.
		AnnounceAnimPauseTime = GetAnimationCurrentTime(VictoryWidgetAnim);
		if(IsAnimationPlaying(VictoryWidgetAnim))
		{
			bAnimationWasPaused = true;
		}
		PauseAnimation(VictoryWidgetAnim);
	}
	else
	{
		if(bAnimationWasPaused == true)
		{
			PlayAnimation(VictoryWidgetAnim, AnnounceAnimPauseTime, 1, EUMGSequencePlayMode::Forward, 1, false);
		}
	}
		
}
