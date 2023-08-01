// Created by Spring2022_Capstone team

#include "SemiAutomaticWeapon.h"

#include "DevTargets.h"
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
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Default Shot");
						break;
					case SURFACE_FleshVulnerable:
						DamageableActor->DamageActor(this, ShotDamage * CriticalHitMultiplier);
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Head Shot");
						break;
					default:
						DamageableActor->DamageActor(this, ShotDamage);
						break;
					}
					ShowHitMarker();
				}
				//DrawDebugLine(GetWorld(), StartTrace, HitResult.Location, FColor::Black, false, 0.5f);
				PlayTracerEffect(HitResult.Location);

			}

			CurrentCharge += ShotCost;
			PlayWeaponCameraShake();

			bIsFiring = true;
			GetWorld()->GetTimerManager().SetTimer(IsFiringToggleTimerHandle, this, &AWeaponBase::ToggleIsFiringOff, 0.05, false);	

			// Call recoil
			if (RecoilComponent)
				RecoilComponent->RecoilKick();
		}
	}
}
