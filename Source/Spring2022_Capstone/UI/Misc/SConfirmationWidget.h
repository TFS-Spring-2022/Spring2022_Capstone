// Created by Spring2022_Capstone team

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 *
 */
class SPRING2022_CAPSTONE_API SConfirmationWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SConfirmationWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMainMenuHUD>, MenuHUD)

	SLATE_END_ARGS()

	void Construct(const FArguments &InArgs);

	FReply OnConfirmationClicked();
	FReply OnCancelClicked();

	TWeakObjectPtr<class AMainMenuHUD> MenuHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };
};
