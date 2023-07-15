// Created by Spring2022_Capstone team


#include "DirectionalDamageIndicatorWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

void UDirectionalDamageIndicatorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
}

void UDirectionalDamageIndicatorWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if(DamagingActor)
	{
		float DamagingEnemyLookAtRotationYaw = UKismetMathLibrary::FindLookAtRotation(Player->GetActorLocation(), DamagingActor->GetActorLocation()).Yaw;
		DamagingEnemyLookAtRotationYaw -= Player->GetControlRotation().Yaw; // Set direction for Damage Indicator Image rotation.

		// ToDo: lerp to rotation (when we switch to setting intial location 
		DamageIndicatorImage->SetRenderTransformAngle(DamagingEnemyLookAtRotationYaw);;
		// ToDo: Make Visible/Invisible with timer
	}
}

void UDirectionalDamageIndicatorWidget::SetDamagingActor(AActor* Damager)
{
	DamagingActor = Damager;
}

