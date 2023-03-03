// Created by Spring2022_Capstone team

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class ATitleScreenHUD;
class ATitleScreenHUD;

class SPRING2022_CAPSTONE_API STitleScreenWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STitleScreenWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<ATitleScreenHUD>, TitleScreenHUD)

	SLATE_END_ARGS()

	void Construct(const FArguments &InArgs);

	FReply OnAnyPressed() const;

	TWeakObjectPtr<ATitleScreenHUD> TitleScreenHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };
};