// Created by Spring2022_Capstone team

#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/PlayerCharacter.h"

void UHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (APlayerCharacter *playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
    {
        playerCharacter->OnHealthChangedDelegate.BindUObject(this, &UHUDWidget::OnHealthChanged);
        playerCharacter->OnGrappleTriggeredDelegate.BindUObject(this, &UHUDWidget::OnGrappleTriggered);
    }

    GrappleCooldown = 0.f;
}

void UHUDWidget::NativeTick(const FGeometry &MyGeometry, float DeltaTime)
{
    Super::NativeTick(MyGeometry, DeltaTime);
    if (GrappleTimerHandle && GrappleTimerHandle->IsValid())
    {
        // UE_LOG(LogTemp, Display, TEXT("%f"), UKismetSystemLibrary::K2_GetTimerRemainingTimeHandle(GetWorld(), *GrappleTimerHandle));
    }
}

void UHUDWidget::OnHealthChanged(float HealthValue)
{
    HealthBar->SetPercent(HealthValue / 100);
}

void UHUDWidget::OnGrappleTriggered(FTimerHandle &TimerHandle)
{
    GrappleTimerHandle = &TimerHandle;
}
