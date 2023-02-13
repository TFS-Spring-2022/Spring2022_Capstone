// Created by Spring2022_Capstone team

#include "STitleScreenWidget.h"
#include "TitleScreenHUD.h"

#define LOCTEXT_NAMESPACE "TitleScreenHUD"

void STitleScreenWidget::Construct(const FArguments &InArgs)
{
    bCanSupportFocus = true;

    TitleScreenHUD = InArgs._TitleScreenHUD;

    const FMargin ContentPadding = FMargin(500.f, 300.f);
    const FMargin ButtonPadding = FMargin(10.f);

    ChildSlot [
        SNew(SOverlay)
        + SOverlay::Slot()
        .HAlign(HAlign_Fill)
        .VAlign(VAlign_Fill)
        [
            SNew(SImage)
            .ColorAndOpacity(FColor::Blue)
        ]
    ];
}

FReply STitleScreenWidget::OnAnyPressed() const
{
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE