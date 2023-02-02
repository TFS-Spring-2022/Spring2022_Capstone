// Created by Spring2022_Capstone team

#include "SConfirmationWidget.h"
#include "Spring2022_Capstone/MainMenu/MainMenuHUD.h"

#define LOCTEXT_NAMESPACE "Confirmation"

void SConfirmationWidget::Construct(const FArguments &InArgs)
{
    bCanSupportFocus = true;

    MenuHUD = InArgs._MenuHUD;

    const FMargin ContentPadding = FMargin(500.f, 300.f);
    const FMargin ButtonPadding = FMargin(10.f);

    const FText DialogText = LOCTEXT("DialogText", "Do you want to continue?");
    const FText ConfirmText = LOCTEXT("Confirm", "Yes");
    const FText CancelText = LOCTEXT("Cancel", "Cancel");

    FSlateFontInfo DialogTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
    DialogTextStyle.Size = 60.f;

    FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
    ButtonTextStyle.Size = 40.f;

    ChildSlot [
        SNew(SOverlay)
        + SOverlay::Slot()
        .HAlign(HAlign_Fill)
        .VAlign(VAlign_Fill)
        [
            SNew(SImage)
            .ColorAndOpacity(FColor::Red)
        ]
        + SOverlay::Slot()
        .HAlign(HAlign_Fill)
        .VAlign(VAlign_Fill)
        .Padding(ContentPadding)
        [
            SNew(SVerticalBox)

            // Dialog Text
            + SVerticalBox::Slot()
            [
                SNew(STextBlock)
                .Font(DialogTextStyle)
                .Text(DialogText)
                .Justification(ETextJustify::Center)
            ]
            
            // Confirm Button
            + SVerticalBox::Slot() 
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                [
                    SNew(SButton)
                    .OnClicked(this, &SConfirmationWidget::OnConfirmationClicked)
                    [
                        SNew(STextBlock)
                        .Font(DialogTextStyle)
                        .Text(ConfirmText)
                        .Justification(ETextJustify::Center)
                    ]
                ]

                + SHorizontalBox::Slot()
                [
                    SNew(SButton)
                    .OnClicked(this, &SConfirmationWidget::OnCancelClicked)
                    [
                        SNew(STextBlock)
                        .Font(DialogTextStyle)
                        .Text(CancelText)
                        .Justification(ETextJustify::Center)
                    ]
                ]
            ]
        ]
    ];
}

FReply SConfirmationWidget::OnConfirmationClicked()
{
    MenuHUD->ExitGame();
    return FReply::Handled();
}

FReply SConfirmationWidget::OnCancelClicked()
{
    MenuHUD->RemoveQuitConfirmation();
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE