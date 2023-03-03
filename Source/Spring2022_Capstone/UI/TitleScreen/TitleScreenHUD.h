// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TitleScreenHUD.generated.h"

class STitleScreenWidget;
class SWidget;

UCLASS()
class SPRING2022_CAPSTONE_API ATitleScreenHUD : public AHUD
{
	GENERATED_BODY()

protected:
	TSharedPtr<STitleScreenWidget> TitleScreenWidget;
	TSharedPtr<SWidget> TitleScreenContainer;

	virtual void BeginPlay() override;

public: 

	void ShowMenu();
};