// Created by Spring2022_Capstone team

#include "EndScreenUserWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
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
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC, this);
	}

	ScoreSystemManager = GetGameInstance()->GetSubsystem<UScoreSystemManagerSubSystem>();
	SetScoreStatTextBoxes();
	SetAccoladeTextBoxes();
}

void UEndScreenUserWidget::ReturnToMenuButtonPressed()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}

void UEndScreenUserWidget::OnExitButtonPressed()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

void UEndScreenUserWidget::SetScoreStatTextBoxes()
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

void UEndScreenUserWidget::SetAccoladeTextBoxes()
{
	if(!ScoreSystemManager)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "SCORE SYSTEM MANAGER DOESN'T EXIST");
		return;
	}
	
	const FString SkullNCrosshairTextValue = FString::Printf(TEXT("Skull N' Crosshairs: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::SkullNCrosshair)));
	SkullNCrosshairTextBlock->SetText(FText::FromString(SkullNCrosshairTextValue));
	
	const FString CaptainOfWarTextValue = FString::Printf(TEXT("Captain Of War: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::CaptainOfWar)));
	CaptainOfWarTextBlock->SetText(FText::FromString(CaptainOfWarTextValue));

	const FString SkyPirateTextValue = FString::Printf(TEXT("Sky Pirate: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::SkyPirate)));
	SkyPirateTextBlock->SetText(FText::FromString(SkyPirateTextValue));

	const FString LandLubberTextValue = FString::Printf(TEXT("Land Lubber: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::LandLubber)));
	LandLubberTextBlock->SetText(FText::FromString(LandLubberTextValue));

	const FString CloseCallCorsairTextValue = FString::Printf(TEXT("Close Call Corsair: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::CloseCallCorsair)));
	CloseCallCorsairTextBlock->SetText(FText::FromString(CloseCallCorsairTextValue));

	const FString OpportunistTextValue = FString::Printf(TEXT("Opportunist: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::Opportunist)));
	OpportunistTextBlock->SetText(FText::FromString(OpportunistTextValue));

	const FString CaptainsCoupTextValue = FString::Printf(TEXT("Captains Coup: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::CaptainsCoup)));
	CaptainsCoupTextBlock->SetText(FText::FromString(CaptainsCoupTextValue));

	const FString DoubleAerialPlunderTextValue = FString::Printf(TEXT("Double Aerial Plunder: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::DoubleAerialPlunder)));
	DoubleAerialPlunderTextBlock->SetText(FText::FromString(DoubleAerialPlunderTextValue));

	const FString BlunderBlastTextValue = FString::Printf(TEXT("Blunder Blast: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::BlunderBlast)));
	BlunderBlastTextBlock->SetText(FText::FromString(BlunderBlastTextValue));

	const FString SkyBuccaneerTextValue = FString::Printf(TEXT("Sky Buccaneer: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::SkyBuccaneer)));
	SkyBuccaneerTextBlock->SetText(FText::FromString(SkyBuccaneerTextValue));

	const FString HotHeadedTextValue = FString::Printf(TEXT("Hot Headed: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::HotHeaded)));
	HotHeadedTextBlock->SetText(FText::FromString(HotHeadedTextValue));

	const FString NimbleBonesTextValue = FString::Printf(TEXT("Nimble Bones: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::NimbleBones)));
	NimbleBonesTextBlock->SetText(FText::FromString(NimbleBonesTextValue));
	
	const FString DeathDodgerTextValue = FString::Printf(TEXT("Death Dodger: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::DeathDodger)));
	DeathDodgerTextBlock->SetText(FText::FromString(DeathDodgerTextValue));
	
	const FString PiratesFortitudeTextValue = FString::Printf(TEXT("Pirates Fortitude: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::PiratesFortitude)));
	PiratesFortitudeTextBlock->SetText(FText::FromString(PiratesFortitudeTextValue));
	
	const FString PlunderersProwessTextValue = FString::Printf(TEXT("Plunderers Prowess: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::PlunderersProwess)));
	PlunderersProwessTextBlock->SetText(FText::FromString(PlunderersProwessTextValue));
	
	const FString IPreferTreasureTextValue = FString::Printf(TEXT("I Prefer Treasure: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::IPreferTreasure)));
	IPreferTreasureTextBlock->SetText(FText::FromString(IPreferTreasureTextValue));
	
	const FString PirateBlitzTextValue = FString::Printf(TEXT("Pirate Blitz: %d"), (ScoreSystemManager->GetAccoladeCount(EAccolades::PirateBlitz)));
	PirateBlitzTextBlock->SetText(FText::FromString(PirateBlitzTextValue));
	
}
