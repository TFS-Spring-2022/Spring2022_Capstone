// Created by Spring2022_Capstone team

#include "EndScreenUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UEndScreenUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReturnToMainMenuButton->OnClicked.AddUniqueDynamic(this, &UEndScreenUserWidget::ReturnToMenuButtonPressed);
	ExitButton->OnClicked.AddUniqueDynamic(this, &UEndScreenUserWidget::OnExitButtonPressed);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}

	ScoreSystemManager = GetGameInstance()->GetSubsystem<UScoreSystemManagerSubSystem>();
	SetScoreStatsTextBox();
}

void UEndScreenUserWidget::ReturnToMenuButtonPressed()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}

void UEndScreenUserWidget::OnExitButtonPressed()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

void UEndScreenUserWidget::SetScoreStatsTextBox()
{
	if(!ScoreSystemManager)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "SCORE SYSTEM MANAGER DOESN'T EXIST");
		return;
	}

	const FString HitTextValue = FString::Printf(TEXT("Hits: %d"), static_cast<int>(ScoreSystemManager->GetCounterValue(EScoreCounters::Hits)));
	HitsTextBlock->SetText(FText::FromString(HitTextValue));

	const FString HeadshotsTextValue = FString::Printf(TEXT("Headshots: %d"), static_cast<int>(ScoreSystemManager->GetCounterValue(EScoreCounters::HeadshotHits)));
	HeadshotsTextBlock->SetText(FText::FromString(HeadshotsTextValue));

	const FString HitsWhileAirborneTextValue = FString::Printf(TEXT("Airborne Hits: %d"), static_cast<int>(ScoreSystemManager->GetCounterValue(EScoreCounters::HitsWhileAirborne)));
	HitsWhileAirborneTextBlock->SetText(FText::FromString(HitsWhileAirborneTextValue));

	const FString EnemiesKilledTextValue = FString::Printf(TEXT("Enemies Killed: %d"), static_cast<int>(ScoreSystemManager->GetCounterValue(EScoreCounters::EnemiesKilled)));
	EnemiesKilledTextBlock->SetText(FText::FromString(EnemiesKilledTextValue));

	const FString EnemiesKilledWithHazardsTextValue = FString::Printf(TEXT("Enemies Killed With Hazards: %d"), static_cast<int>(ScoreSystemManager->GetCounterValue(EScoreCounters::EnemiesKilledWithHazards)));
	EnemiesKilledWithHazardsTextBlock->SetText(FText::FromString(EnemiesKilledWithHazardsTextValue));

	const FString ElitesKilledTextValue = FString::Printf(TEXT("Elites Killed: %d"), static_cast<int>(ScoreSystemManager->GetCounterValue(EScoreCounters::ElitesKilled)));
	ElitesKilledTextBlock->SetText(FText::FromString(ElitesKilledTextValue));

	const FString SnipersDisabledTextValue = FString::Printf(TEXT("Snipers Disabled: %d"), static_cast<int>(ScoreSystemManager->GetCounterValue(EScoreCounters::SnipersDisabled)));
	SnipersDisabledTextBlock->SetText(FText::FromString(SnipersDisabledTextValue));
	
}
