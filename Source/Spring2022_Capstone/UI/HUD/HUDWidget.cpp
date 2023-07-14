// Created by Spring2022_Capstone team

#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "Spring2022_Capstone/Weapon/WeaponBase.h"
#include "Spring2022_Capstone/Player/GrappleComponent.h"

void UHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    if (PlayerRef != nullptr)
    {
        PlayerRef->OnHealthChangedDelegate.BindUObject(this, &UHUDWidget::OnHealthChanged);
        PlayerRef->OnDamagedDelegate.BindUObject(this, &UHUDWidget::PlayCrosshairAnimation);
        

        MaxHealth = PlayerRef->GetMaxHealth();
        if (UGrappleComponent *GrappleComponent = PlayerRef->GetGrappleComponent())
        {
            GrappleComponent->OnGrappleActivatedDelegate.BindUObject(this, &UHUDWidget::OnGrappleActivated);
            GrappleComponent->OnGrappleCooldownStartDelegate.BindUObject(this, &UHUDWidget::OnGrappleCooldownStart);
            GrappleComponent->OnGrappleCooldownEndDelegate.BindUObject(this, &UHUDWidget::OnGrappleCooldownEnd);
        }
    }

    GrappleCooldownText->SetText(FText::GetEmpty());
}

void UHUDWidget::PlayCrosshairAnimation()
{
    if (CrosshairAnimation == nullptr) return;

    PlayAnimation(CrosshairAnimation, 0.0f, 1, EUMGSequencePlayMode::PingPong);
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

    if (PlayerRef != nullptr)
    {
        AWeaponBase* CurrentWeapon = PlayerRef->GetActiveWeapon();
        if (CurrentWeapon != nullptr)
        {

            if (OverheatBar == nullptr) return;
            OverheatBar->SetPercent(CurrentWeapon->CurrentCharge / 100);
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
