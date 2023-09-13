// Created by Spring2022_Capstone team

#include "SemiAutomaticWeapon.h"

#include "DevTargets.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"

#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Spring2022_Capstone/Spring2022_Capstone.h"
#include "Spring2022_Capstone/Enemies/BaseEnemy.h"
#include "Spring2022_Capstone/EnvironmentObjects/Hazards/Barrel.h"


ASemiAutomaticWeapon::ASemiAutomaticWeapon()
{

	RecoilComponent = CreateDefaultSubobject<URecoilComponent>("SemiAuto Recoil Component");
}

bool ASemiAutomaticWeapon::Shoot()
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
					
					if(DamageableActor->_getUObject()->IsA(ABarrel::StaticClass()))
					{
						DamageableActor->DamageActor(this, ShotDamage);
						if(FloatingDamageNumberParticleSystem)
							DisplayFloatingDamageNumbers(HitResult.Location, ShotDamage, false);
					}
					else if (!Cast<ABaseEnemy>(HitResult.GetActor())->GetIsDying())
					{
						if(ScoreManagerSubSystem)
						{
							// Increment hit counter
							ScoreManagerSubSystem->IncrementScoreCounter(EScoreCounters::Hits);
				
							// If player is in the air, increment counter
							if(!PlayerCharacter->GetMovementComponent()->IsMovingOnGround())
								ScoreManagerSubSystem->IncrementScoreCounter(EScoreCounters::HitsWhileAirborne);
						}
						
						switch (HitSurfaceType)
						{
						case SURFACE_FleshDefault:
							if(DamageableActor->DamageActor(this, ShotDamage, HitResult.BoneName))
							{
								if (!PlayerCharacter->GetMovementComponent()->IsMovingOnGround())
									SoundManagerSubSystem->PlayPlayerSoundEvent(PlayerCharacter->PlayerVoiceAudioComp, 9);
							}
							if(FloatingDamageNumberParticleSystem)
								DisplayFloatingDamageNumbers(HitResult.Location, ShotDamage, false);
							break;
						case SURFACE_FleshVulnerable:
							
							//Coin flip for voiceline
							if(SoundManagerSubSystem)
							{
								if(FMath::RandRange(1,2) == 1)
									SoundManagerSubSystem->PlayPlayerSoundEvent(PlayerCharacter->PlayerVoiceAudioComp,6);
								else
									SoundManagerSubSystem->PlayNarratorSoundEvent(PlayerCharacter->PlayerVoiceAudioComp,2);
							}
							
							DamageableActor->DamageActor(this, ShotDamage * CriticalHitMultiplier, HitResult.BoneName);
							if(FloatingDamageNumberParticleSystem)
								DisplayFloatingDamageNumbers(HitResult.Location, ShotDamage * CriticalHitMultiplier, true);

							// Score 
							if(ScoreManagerSubSystem)
								ScoreManagerSubSystem->IncrementScoreCounter(EScoreCounters::HeadshotHits);
							// Skull N Crosshair Accolade
							if(ScoreManagerTimerSubSystem)
							{
								if(ScoreManagerTimerSubSystem->IsAccoladeTimerRunning(EAccolades::SkullNCrosshair))
									ScoreManagerTimerSubSystem->IncrementScullNCrosshairHeadshotHits();
								else
									ScoreManagerTimerSubSystem->StartAccoladeTimer(EAccolades::SkullNCrosshair);
							}
							break;
						default:
							DamageableActor->DamageActor(this, ShotDamage, HitResult.BoneName);
							break;
						}
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
			
			return true;
		}
	}
	return false;
}
