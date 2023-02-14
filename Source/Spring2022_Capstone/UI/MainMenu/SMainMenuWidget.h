// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class AMainMenuHUD;

class SPRING2022_CAPSTONE_API SMainMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainMenuWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<AMainMenuHUD>, MenuHUD)

	SLATE_END_ARGS()

	void Construct(const FArguments &InArgs);

	FReply OnPlayClicked() const;
	FReply OnSettingsClicked() const;
	FReply OnCreditsClicked() const;
	FReply OnQuitClicked() const;

	TWeakObjectPtr<AMainMenuHUD> MenuHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };
};
