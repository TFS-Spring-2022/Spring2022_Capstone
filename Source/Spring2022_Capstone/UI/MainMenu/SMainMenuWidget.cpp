// Fill out your copyright notice in the Description page of Project Settings.

#include "SMainMenuWidget.h"
#include "MainMenuHUD.h"
#include "Engine/LevelStreamingDynamic.h"


#define LOCTEXT_NAMESPACE "MainMenu"

void SMainMenuWidget::Construct(const FArguments &InArgs)
{
    bCanSupportFocus = true;

    MenuHUD = InArgs._MenuHUD;

    const FMargin ContentPadding = FMargin(500.f, 300.f);
    const FMargin ButtonPadding = FMargin(10.f);

    const FText TitleText = LOCTEXT("GameTitle", "SkyPirates");
    const FText PlayText = LOCTEXT("PlayGame", "Play");
    const FText SettingsText = LOCTEXT("Settings", "Settings");
    const FText CreditsText = LOCTEXT("Credits", "Credits");
    const FText QuitText = LOCTEXT("QuitGame", "Quit Game");

    FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
    ButtonTextStyle.Size = 40.f;

    FSlateFontInfo TitleTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
    TitleTextStyle.Size = 60.f;
    
    ChildSlot [
        SNew(SOverlay)
        + SOverlay::Slot()
        .HAlign(HAlign_Fill)
        .VAlign(VAlign_Fill)
        [
            SNew(SImage)
            .ColorAndOpacity(FColor::Blue)
        ]
        + SOverlay::Slot()
        .HAlign(HAlign_Fill)
        .VAlign(VAlign_Fill)
        .Padding(ContentPadding)
        [
            SNew(SVerticalBox)

            // Title text
            + SVerticalBox::Slot()
            [
                SNew(STextBlock)
                .Font(TitleTextStyle)
                .Text(TitleText)
                .Justification(ETextJustify::Center)
            ]

            // Play Button
            +SVerticalBox::Slot()
            .Padding(ButtonPadding)
            [
                SNew(SButton)
                .OnClicked(this, &SMainMenuWidget::OnPlayClicked)
                [
                    SNew(STextBlock)
                    .Font(ButtonTextStyle)
                    .Text(PlayText)
                    .Justification(ETextJustify::Center)
                ]
            ]

            // Settings Button
            +SVerticalBox::Slot()
            .Padding(ButtonPadding)
            [
                SNew(SButton)
                .OnClicked(this, &SMainMenuWidget::OnSettingsClicked)
                [
                    SNew(STextBlock)
                    .Font(ButtonTextStyle)
                    .Text(SettingsText)
                    .Justification(ETextJustify::Center)
                ]
            ]

            // Credits Button
            +SVerticalBox::Slot()
            .Padding(ButtonPadding)
            [
                SNew(SButton)
                .OnClicked(this, &SMainMenuWidget::OnCreditsClicked)
                [
                    SNew(STextBlock)
                    .Font(ButtonTextStyle)
                    .Text(CreditsText)
                    .Justification(ETextJustify::Center)
                ]
            ]

            // Quit Button
            +SVerticalBox::Slot()
            .Padding(ButtonPadding)
            [
                SNew(SButton)
                .OnClicked(this, &SMainMenuWidget::OnQuitClicked)
                [
                    SNew(STextBlock)
                    .Font(ButtonTextStyle)
                    .Text(QuitText)
                    .Justification(ETextJustify::Center)
                ]
            ]
        ]
    ];
}

FReply SMainMenuWidget::OnPlayClicked() const
{
    UE_LOG(LogTemp, Log, TEXT("Play Clicked"));
    // TODO: Open new level
    return FReply::Handled();
}

FReply SMainMenuWidget::OnSettingsClicked() const
{
    UE_LOG(LogTemp, Log, TEXT("Settings Clicked"));
    // ULevelStreamingDynamic::
    return FReply::Handled();
}

FReply SMainMenuWidget::OnCreditsClicked() const
{
    UE_LOG(LogTemp, Log, TEXT("Credits Clicked"));
    // TODO: Open Credits
    return FReply::Handled();
}

FReply SMainMenuWidget::OnQuitClicked() const
{
    UE_LOG(LogTemp, Log, TEXT("Quit Clicked"));
    MenuHUD->ShowQuitConfirmation();
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE