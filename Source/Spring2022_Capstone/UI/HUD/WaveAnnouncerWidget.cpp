// Created by Spring2022_Capstone team


#include "WaveAnnouncerWidget.h"

void UWaveAnnouncerWidget::SetAnnouncementTextBlock(FText Announcement)
{
	if(!AnnouncementTextBlock)
		return;

	AnnouncementTextBlock->SetText(Announcement);

	// Play text block entrance animation.
	PlayAnimation(AnnounceWidgetAnim, 0, 1, EUMGSequencePlayMode::Forward, 1, false);
}
