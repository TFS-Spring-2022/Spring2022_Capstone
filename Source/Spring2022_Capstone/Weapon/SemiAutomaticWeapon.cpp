// Created by Spring2022_Capstone team

#include "SemiAutomaticWeapon.h"

#include "DevTargets.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"

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
				// Get Surface Type to check for headshot and impact material type.
				EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
				
				if (HitResult.GetActor()->Implements<UDamageableActor>())
				{

					IDamageableActor *DamageableActor = Cast<IDamageableActor>(HitResult.GetActor());
					
					switch (HitSurfaceType)
					{
					case SURFACE_FleshDefault:
						DamageableActor->DamageActor(this, ShotDamage, HitResult.BoneName);
						if(FloatingDamageNumberParticleSystem)
							DisplayFloatingDamageNumbers(HitResult.Location, ShotDamage, false);
						break;
					case SURFACE_FleshVulnerable:
						DamageableActor->DamageActor(this, ShotDamage * CriticalHitMultiplier, HitResult.BoneName);
						if(FloatingDamageNumberParticleSystem)
							DisplayFloatingDamageNumbers(HitResult.Location, ShotDamage * CriticalHitMultiplier, true);
						break;
					default:
						DamageableActor->DamageActor(this, ShotDamage, HitResult.BoneName);
						break;
					}
					ShowHitMarker();

					
					
				}
				//DrawDebugLine(GetWorld(), StartTrace, HitResult.Location, FColor::Black, false, 0.5f);
				PlayTracerEffect(HitResult.Location);

				
				switch (HitSurfaceType)
				{
				case SURFACE_FleshDefault:
				case SURFACE_FleshVulnerable:
					ImpactEffectToPlay = FleshImpactParticleSystem;
					break;
				default:
					ImpactEffectToPlay = RockImpactParticleSystem; // ToDo: Setup default once all custom Surface Types are made.
					break;
				}
				if(ImpactEffectToPlay)
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffectToPlay, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
			}
			
			if(MuzzleFlashParticleSystem)
				UGameplayStatics::SpawnEmitterAttached(MuzzleFlashParticleSystem, SkeletalMesh, ShootingStartSocket);
			
			CurrentCharge += ShotCost;
			PlayWeaponCameraShake();

			bIsFiring = true;
			GetWorld()->GetTimerManager().SetTimer(IsFiringToggleTimerHandle, this, &AWeaponBase::ToggleIsFiringOff, 0.05, false);	

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
