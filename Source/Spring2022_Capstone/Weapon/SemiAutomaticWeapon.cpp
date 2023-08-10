// Created by Spring2022_Capstone team

#include "SemiAutomaticWeapon.h"

#include "DamageNumberWidget.h"
#include "DevTargets.h"
#include "Kismet/GameplayStatics.h"

#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Spring2022_Capstone/Spring2022_Capstone.h"


ASemiAutomaticWeapon::ASemiAutomaticWeapon()
{

	RecoilComponent = CreateDefaultSubobject<URecoilComponent>("SemiAuto Recoil Component");
}

void ASemiAutomaticWeapon::Shoot()
{

	if (!bIsOverheating && CurrentCharge > MaxChargeAmount)
	{
		Overheat();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("OVERHEATING"));
	}

	if (bCanFire)
	{

		if (!GetWorldTimerManager().IsTimerActive(FireTimerHandle))
		{
			// Start timer the fire rate timer (after it runs for FireRate (time between shots in seconds) it will be cleared
			GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASemiAutomaticWeapon::ClearFireTimerHandle, FireRate, false);

			FHitResult HitResult;

			FVector StartTrace = PlayerCamera->GetCameraLocation();
			StartTrace.Z -= 10; // TEMP: Offset to make debug draw lines visible without moving.
			FVector ForwardVector = PlayerCamera->GetActorForwardVector();
			FVector EndTrace = ((ForwardVector * ShotDistance) + StartTrace);
			FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
			TraceParams->bReturnPhysicalMaterial = true;  // Hit must return a physical material to tell if the player has hit a headshot.
			TraceParams->AddIgnoredComponent(PlayerCharacter->GetMesh());
			
			if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
			{
				
				if (HitResult.GetActor()->Implements<UDamageableActor>())
				{

					IDamageableActor *DamageableActor = Cast<IDamageableActor>(HitResult.GetActor());

					// Get Surface Type to check if headshot
					EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
					
					switch (HitSurfaceType)
					{
					case SURFACE_FleshDefault:
						DamageableActor->DamageActor(this, ShotDamage);
						GEngine->AddOnScreenDebugMessage(11, .5f, FColor::Black, "Default Shot");
						break;
					case SURFACE_FleshVulnerable:
						DamageableActor->DamageActor(this, ShotDamage * CriticalHitMultiplier);
						GEngine->AddOnScreenDebugMessage(10, .5f, FColor::Red, "Head Shot");
						break;
					default:
						DamageableActor->DamageActor(this, ShotDamage);
						break;
						
					}
					float DamageDealt = (HitSurfaceType == SURFACE_FleshVulnerable) ? (ShotDamage * CriticalHitMultiplier) : ShotDamage;

					// Spawn the damage number widget
					/*
					if (UDamageNumberWidget* DamageNumberWidget = CreateWidget<UDamageNumberWidget>(GetWorld(), DamageNumberWidgetClass))
					{
						DamageNumberWidget->SetDamageText(FText::AsNumber(DamageDealt));
						DamageNumberWidget->SetColorBySurfaceType(HitSurfaceType);
						DamageNumberWidget->AddToViewport();

						// You can set the widget's position based on the hit location

						if (APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController()))
						{
							FVector2D ScreenPosition;
							if (UGameplayStatics::ProjectWorldToScreen(PlayerController, HitResult.Location, ScreenPosition))
							{
								DamageNumberWidget->SetPositionInViewport(ScreenPosition);
							}
						}

						// Schedule the widget to be removed after 2 seconds
						DamageNumberWidget->GetWorld()->GetTimerManager().SetTimer(
							DamageNumberWidget->DespawnTimerHandle, 
							FTimerDelegate::CreateUObject(DamageNumberWidget, &UDamageNumberWidget::Despawn), 
							2.0f, false);
					ShowHitMarker();
					*/
				}
				DrawDebugLine(GetWorld(), StartTrace, HitResult.Location, FColor::Black, false, 0.5f);
			}
			
			if(CurrentCharge == 0)
			{
				OverheatAudioComp->Play();
			}

			CurrentCharge += ShotCost;
			PlayWeaponCameraShake();

			if(OverheatAudioComp)
			{
				OverheatAudioComp->SetPitchMultiplier((CurrentCharge/MaxChargeAmount));
			}

			//Play gun sound
            if(GunShotAudioComp)
            {
            	GunShotAudioComp->Play();
            }
			
			// Call recoil
			if (RecoilComponent)
				RecoilComponent->RecoilKick();
		}
	}
}
