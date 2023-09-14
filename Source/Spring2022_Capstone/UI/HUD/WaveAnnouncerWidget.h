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

private:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* AnnouncementTextBlock;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnnounceWidgetAnim;
	
public:

	void SetAnnouncementTextBlock(FText Announcement);
};
