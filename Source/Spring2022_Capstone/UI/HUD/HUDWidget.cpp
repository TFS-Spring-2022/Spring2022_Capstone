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
        playerCharacter->OnGrappleActivatedDelegate.BindUObject(this, &UHUDWidget::OnGrappleActivated);
        playerCharacter->OnGrappleCooldownStartDelegate.BindUObject(this, &UHUDWidget::OnGrappleCooldownStart);
        playerCharacter->OnGrappleCooldownEndDelegate.BindUObject(this, &UHUDWidget::OnGrappleCooldownEnd);
    }

    GrappleCooldown = 0.f;
}

void UHUDWidget::NativeTick(const FGeometry &MyGeometry, float DeltaTime)
{
    Super::NativeTick(MyGeometry, DeltaTime);
    if (GrappleTimerHandle && GrappleTimerHandle->IsValid())
    {
        float grappleCooldownPercent = UKismetSystemLibrary::K2_GetTimerRemainingTimeHandle(GetWorld(), *GrappleTimerHandle) / 5.f;
        GrappleCooldownBar->SetPercent(grappleCooldownPercent);
    }
}

void UHUDWidget::OnHealthChanged(float HealthValue)
{
    HealthBar->SetPercent(HealthValue / 100);
}

void UHUDWidget::OnGrappleActivated()
{
    GrappleCooldownBar->SetPercent(1);
}

void UHUDWidget::OnGrappleCooldownStart(FTimerHandle &TimerHandle)
{
    GrappleTimerHandle = &TimerHandle;
}

void UHUDWidget::OnGrappleCooldownEnd()
{
    GrappleTimerHandle = nullptr;
    GrappleCooldownBar->SetPercent(0);
}
