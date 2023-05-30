// Created by Spring2022_Capstone team

#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "Spring2022_Capstone/Player/GrappleComponent.h"

void UHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
    {
        PlayerCharacter->OnHealthChangedDelegate.BindUObject(this, &UHUDWidget::OnHealthChanged);
        MaxHealth = PlayerCharacter->GetMaxHealth();
        if (UGrappleComponent *GrappleComponent = PlayerCharacter->GetGrappleComponent())
        {
            GrappleComponent->OnGrappleActivatedDelegate.BindUObject(this, &UHUDWidget::OnGrappleActivated);
            GrappleComponent->OnGrappleCooldownStartDelegate.BindUObject(this, &UHUDWidget::OnGrappleCooldownStart);
            GrappleComponent->OnGrappleCooldownEndDelegate.BindUObject(this, &UHUDWidget::OnGrappleCooldownEnd);
        }
    }

    GrappleCooldownText->SetText(FText::GetEmpty());
}

void UHUDWidget::NativeTick(const FGeometry &MyGeometry, float DeltaTime)
{
    Super::NativeTick(MyGeometry, DeltaTime);
    if (GrappleTimerHandle && GrappleTimerHandle->IsValid())
    {
        float timerRemainingTime = UKismetSystemLibrary::K2_GetTimerRemainingTimeHandle(GetWorld(), *GrappleTimerHandle);
        float grappleCooldownPercent = timerRemainingTime / GrappleCooldown;
        GrappleCooldownBar->SetPercent(grappleCooldownPercent);
        GrappleCooldownText->SetText(FText::FromString(FString::FromInt(FMath::CeilToInt(timerRemainingTime))));
    }
}

void UHUDWidget::OnHealthChanged(float HealthValue)
{
    HealthBar->SetPercent(HealthValue / MaxHealth);
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
    GrappleCooldownText->SetText(FText::GetEmpty());
}
