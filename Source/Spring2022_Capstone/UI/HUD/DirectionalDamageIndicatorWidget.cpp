// Created by Spring2022_Capstone team


#include "DirectionalDamageIndicatorWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

void UDirectionalDamageIndicatorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Start invisible
	DamageIndicatorImage->SetRenderOpacity(0);
	
}

void UDirectionalDamageIndicatorWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	
	if(DamagingActor)
	{
		float DamagingEnemyLookAtRotationYaw = UKismetMathLibrary::FindLookAtRotation(Player->GetActorLocation(), DamagingActor->GetActorLocation()).Yaw;
		DamagingEnemyLookAtRotationYaw -= Player->GetControlRotation().Yaw; // Set direction for Damage Indicator Image rotation.

		// ToDo: lerp to rotation (If we switch from AActor* to FVector) 
		DamageIndicatorImage->SetRenderTransformAngle(DamagingEnemyLookAtRotationYaw);;
	}

	if(bFadingIn)
		DamageIndicatorImage->SetRenderOpacity(FMath::FInterpTo(DamageIndicatorImage->GetRenderOpacity(), 1, DeltaTime, NOTIFICATION_FADEIN_SPEED));
	else if(bFadingOut)
		DamageIndicatorImage->SetRenderOpacity(FMath::FInterpTo(DamageIndicatorImage->GetRenderOpacity(), 0, DeltaTime, NOTIFICATION_FADEOUT_SPEED));
	
}

void UDirectionalDamageIndicatorWidget::SetDamagingActor(AActor* Damager)
{
	DamagingActor = Damager;
	StartNotification();
}

void UDirectionalDamageIndicatorWidget::StartNotification()
{
	bFadingIn = true;
	GetWorld()->GetTimerManager().SetTimer(NotificationVisibilityTimerHandle, this, &UDirectionalDamageIndicatorWidget::HideNotification, VisibilityTime, false);
}

void UDirectionalDamageIndicatorWidget::HideNotification()
{
	bFadingIn = false;
	bFadingOut = true;
	DamagingActor = nullptr;
}
