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
    
    PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

    if (PlayerCharacter)
    {
        PlayerCharacter->OnHealthChangedDelegate.BindUObject(this, &UHUDWidget::OnHealthChanged);
        PlayerCharacter->OnDamagedDelegate.BindUObject(this, &UHUDWidget::PlayHitMarkerAnimation);
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

    // ToDo: Clean up
    if(PlayerCharacter)
    {
        AWeaponBase* CurrentWeapon = PlayerCharacter->GetActiveWeapon();
        if(CurrentWeapon)
        {
            if(OverheatBar == nullptr) return;
                OverheatBar->SetPercent(CurrentWeapon->GetCurrentCharge() / 100);
        }
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

void UHUDWidget::PlayHitMarkerAnimation()
{
    if(HitMarkerAnimation)
        PlayAnimation(HitMarkerAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1);
}
