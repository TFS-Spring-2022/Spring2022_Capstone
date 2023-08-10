// Created by Spring2022_Capstone team

#include "ShotgunWeapon.h"

#include "DamageNumberWidget.h"
#include "DevTargets.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "Spring2022_Capstone/Spring2022_Capstone.h"


AShotgunWeapon::AShotgunWeapon()
{
	RecoilComponent = CreateDefaultSubobject<URecoilComponent>("Shotgun Recoil Component");
}

void AShotgunWeapon::Shoot()
{

	if (!bIsOverheating && CurrentCharge > MaxChargeAmount)
	{
		Overheat();
	}

	if (bCanFire)
	{

		if (!GetWorldTimerManager().IsTimerActive(FireTimerHandle))
		{
			// Start timer the fire rate timer (after it runs for FireRate (time between shots in seconds) it will be cleared
			GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AShotgunWeapon::ClearFireTimerHandle, FireRate, false);

			FHitResult HitResult;

			FVector StartTrace = PlayerCamera->GetCameraLocation();
			StartTrace.Z -= 10; // TEMP: Offset to make debug draw lines visible without moving.
			FVector ForwardVector = PlayerCamera->GetActorForwardVector();
			
			// ToDo: UPROPERTY IN HEADER (Naming and Degrees/Radians)	//
			float HalfAngle = 10;
			HalfAngle = UKismetMathLibrary::DegreesToRadians(HalfAngle);
			
			//Play sound												
			if(GunShotAudioComp)
			{
				GunShotAudioComp->Play();
			}

			
			
			for (int i = 0; i < PelletCount; i++)
			{

				// Get random direction inside cone projected from player
				ForwardVector = UKismetMathLibrary::RandomUnitVectorInConeInRadians(PlayerCamera->GetActorForwardVector(), HalfAngle);
				FVector EndTrace = ((ForwardVector * ShotDistance) + StartTrace);
				FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
				TraceParams->bReturnPhysicalMaterial = true; // Hit must return a physical material to tell if the player has hit a headshot.
				TraceParams->AddIgnoredComponent(PlayerCharacter->GetMesh());

				if(GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))

				{
					if (HitResult.GetActor()->Implements<UDamageableActor>())
					{

						// We want to call ShowHitMarker() outside of every shot to prevent unnecessary repeated calls.
						bPelletConnected = true;

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
						

						// Calculate damage based on surface type
						
						float DamageDealt = (HitSurfaceType == SURFACE_FleshVulnerable) ? (ShotDamage * CriticalHitMultiplier) : ShotDamage;

						// Spawn the damage number widget
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
						}

						
					}

					DrawDebugLine(GetWorld(), StartTrace, HitResult.Location, FColor::Black, false, 0.5f);
				}
			}
			if (bPelletConnected)
			{
				ShowHitMarker();
				bPelletConnected = false;
			}
			//Plays the sound if first shot
			if(CurrentCharge == 0)
			{
				OverheatAudioComp->Play();
			}
			
			CurrentCharge += ShotCost;

			
			if(OverheatAudioComp)
			{
				OverheatAudioComp->SetPitchMultiplier((CurrentCharge/MaxChargeAmount));
			}
			PlayWeaponCameraShake();

			

			// Call recoil
			if (RecoilComponent)
				RecoilComponent->RecoilKick();
		}
	}
}
