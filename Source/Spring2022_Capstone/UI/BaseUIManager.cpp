// Created by Spring2022_Capstone team
#include "BaseUIManager.h"
#include "MainMenu/MainMenuWidget.h"
#include "MainMenu/MainMenuManager.h"
#include "Blueprint/UserWidget.h"

ABaseUIManager::ABaseUIManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseUIManager::BeginPlay()
{
	Super::BeginPlay();
	DisplayWidget();
}

void ABaseUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseUIManager::DisplayWidget()
{
	if (RootWidget) {
		_RootWidget = CreateWidget(GetWorld(), RootWidget);

		

		if (UMainMenuWidget *Widget = Cast<UMainMenuWidget>(_RootWidget))
        {
			if(AMainMenuManager *Manager = Cast<AMainMenuManager>(this))
			{
            	Widget->Manager = Manager;
			}
        }

		_RootWidget->AddToViewport(1);

		//
		for (TSubclassOf<UUserWidget> WidgetBluePrint : AdditionalWidgets)
		{
			UUserWidget* _AdditionalWidgetToAdd = CreateWidget(GetWorld(), WidgetBluePrint);
			_AdditionalWidgetToAdd->AddToViewport(1);
		}
		
	} else {
		UE_LOG(LogTemp, Error, TEXT("Type not specizfied for Root Widget"));
	}
}

void ABaseUIManager::DismissWidget()
{
	_RootWidget->RemoveFromParent();
}
