// Created by Spring2022_Capstone team

#include "STitleScreenWidget.h"
#include "TitleScreenHUD.h"

#define LOCTEXT_NAMESPACE "TitleScreenHUD"

void STitleScreenWidget::Construct(const FArguments &InArgs)
{
    bCanSupportFocus = true;

    TitleScreenHUD = InArgs._TitleScreenHUD;
}

FReply STitleScreenWidget::OnAnyPressed() const
{
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE