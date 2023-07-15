// Created by Spring2022_Capstone team


#include "DirectionalDamageIndicatorWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

void UDirectionalDamageIndicatorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
}



