// Created by Spring2022_Capstone team


#include "WaveAnnouncerWidget.h"

void UWaveAnnouncerWidget::SetAnnouncementTextBlock(FText Announcement)
{
	if(!AnnouncementTextBlock)
		return;

	AnnouncementTextBlock->SetText(Announcement);
	PlayAnimation(AnnounceWidgetAnim, 0, 1, EUMGSequencePlayMode::Forward, 1, false);
}

void UWaveAnnouncerWidget::PauseAnnouncementAnimation(bool bIsPaused)
{
	if(bIsPaused)
	{
		// Save current animation time to use when resuming.
		AnnounceAnimPauseTime = GetAnimationCurrentTime(AnnounceWidgetAnim);
		PauseAnimation(AnnounceWidgetAnim);
	}
	else
		PlayAnimation(AnnounceWidgetAnim, AnnounceAnimPauseTime, 1, EUMGSequencePlayMode::Forward, 1, false);
}
