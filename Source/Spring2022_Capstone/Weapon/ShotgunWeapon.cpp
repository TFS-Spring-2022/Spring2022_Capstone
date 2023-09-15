// Created by Spring2022_Capstone team

#include "ShotgunWeapon.h"
#include "DevTargets.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "Spring2022_Capstone/Spring2022_Capstone.h"
#include "Spring2022_Capstone/Enemies/BaseEnemy.h"
#include "Spring2022_Capstone/EnvironmentObjects/Hazards/Barrel.h"
#include "Spring2022_Capstone/EnvironmentObjects/Hazards/Crystal.h"

AShotgunWeapon::AShotgunWeapon()
{
	RecoilComponent = CreateDefaultSubobject<URecoilComponent>("Shotgun Recoil Component");
}

bool AShotgunWeapon::Shoot()
{
	if (!bIsOverheating && CurrentCharge > MaxChargeAmount)
		Overheat();

	if (bCanFire)
	{
		// Enemies killed from a single attack.
		int EnemiesKilledFromAttack = 0;

		if (!GetWorldTimerManager().IsTimerActive(FireTimerHandle))
		{
			TArray<uint32> ActorsKilledWhilePlayerGroundedIDs;
			TArray<uint32> ActorsKilledWhilePlayerAirborneIDs;
			// Start timer the fire rate timer (after it runs for FireRate (time between shots in seconds) it will be cleared
			GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AShotgunWeapon::ClearFireTimerHandle, FireRate, false);

			FHitResult HitResult;

			FVector StartTrace = PlayerCamera->GetCameraLocation();
			StartTrace.Z -= 10; // TEMP: Offset to make debug draw lines visible without moving.
			FVector ForwardVector = PlayerCamera->GetActorForwardVector();

			// ToDo: UPROPERTY IN HEADER (Naming and Degrees/Radians)	//
			float HalfAngle = 10;
			HalfAngle = UKismetMathLibrary::DegreesToRadians(HalfAngle);
			//															//

			if (MuzzleFlashParticleSystem)
				UGameplayStatics::SpawnEmitterAttached(MuzzleFlashParticleSystem, SkeletalMesh, ShootingStartSocket,
													   SkeletalMesh->GetSocketLocation(ShootingStartSocket), SkeletalMesh->GetSocketRotation(ShootingStartSocket));

			bool bHeadshotHit = false; // Used to ensure shotgun headshots don't call for every pellet.

			for (int i = 0; i < PelletCount; i++)
			{
				// Get random direction inside cone projected from player
				ForwardVector = UKismetMathLibrary::RandomUnitVectorInConeInRadians(PlayerCamera->GetActorForwardVector(), HalfAngle);
				FVector EndTrace = ((ForwardVector * ShotDistance) + StartTrace);
				FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
				TraceParams->bReturnPhysicalMaterial = true;
				// Hit must return a physical material to tell if the player has hit a headshot.
				TraceParams->AddIgnoredComponent(PlayerCharacter->GetMesh());

				if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
				{
					// Get Surface Type to check for headshot and impact material.
					EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());

					if (HitResult.GetActor()->Implements<UDamageableActor>())
					{
						// We want to call ShowHitMarker() outside of every shot to prevent unnecessary repeated calls.
						bPelletConnected = true;

						IDamageableActor *DamageableActor = Cast<IDamageableActor>(HitResult.GetActor());

						if (DamageableActor->_getUObject()->IsA(ABarrel::StaticClass()) || DamageableActor->_getUObject()->IsA(ACrystal::StaticClass()))
						{
							DamageableActor->DamageActor(this, ShotDamage);
							if (FloatingDamageNumberParticleSystem)
								DisplayFloatingDamageNumbers(HitResult.Location, ShotDamage, false);
						}
						else if (DamageableActor->_getUObject()->IsA(ABaseEnemy::StaticClass()))
						{

							if (!Cast<ABaseEnemy>(HitResult.GetActor())->GetIsDying())
							{
								if (ScoreManagerSubSystem)
								{
									// Increment hit counter
									ScoreManagerSubSystem->IncrementScoreCounter(EScoreCounters::Hits);

									// If player is in the air, increment counter
									if (!PlayerCharacter->GetMovementComponent()->IsMovingOnGround())
										ScoreManagerSubSystem->IncrementScoreCounter(EScoreCounters::HitsWhileAirborne);
								}

								switch (HitSurfaceType)
								{
								case SURFACE_FleshDefault:
										
									if (DamageableActor->DamageActor(this, ShotDamage, HitResult.BoneName))
									{
										//Enemy has died
										EnemiesKilledFromAttack++;
										CheckIfAirborn(ActorsKilledWhilePlayerGroundedIDs,ActorsKilledWhilePlayerAirborneIDs,HitResult);
									}
									if (FloatingDamageNumberParticleSystem)
										DisplayFloatingDamageNumbers(HitResult.Location, ShotDamage, false);
									break;
								case SURFACE_FleshVulnerable:
									if (DamageableActor->DamageActor(this, ShotDamage * CriticalHitMultiplier,HitResult.BoneName))
									{
										//Enemy has died
										EnemiesKilledFromAttack++;
										CheckIfAirborn(ActorsKilledWhilePlayerGroundedIDs,ActorsKilledWhilePlayerAirborneIDs,HitResult);
									}
									if (FloatingDamageNumberParticleSystem)
										DisplayFloatingDamageNumbers(HitResult.Location, ShotDamage * CriticalHitMultiplier,
																	 true);
									if (ScoreManagerSubSystem)
										ScoreManagerSubSystem->IncrementScoreCounter(EScoreCounters::HeadshotHits);
									bHeadshotHit = true;
									break;
								default:
									if (DamageableActor->DamageActor(this, ShotDamage, HitResult.BoneName))
									{
										//Enemy has died
										EnemiesKilledFromAttack++;
										CheckIfAirborn(ActorsKilledWhilePlayerGroundedIDs,ActorsKilledWhilePlayerAirborneIDs,HitResult);
									}
									break;
								}
							}
						}
					}

					// DrawDebugLine(GetWorld(), StartTrace, HitResult.Location, FColor::Black, false, 0.5f);
					PlayTracerEffect(HitResult.Location);

					switch (HitSurfaceType)
					{
					case SURFACE_FleshDefault:
					case SURFACE_FleshVulnerable:
						ImpactEffectToPlay = FleshImpactParticleSystem;
						break;
					default:
						ImpactEffectToPlay = RockImpactParticleSystem;
						// ToDo: Setup default once all custom Surface Types are made.
						break;
					}
					if (ImpactEffectToPlay)
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffectToPlay, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
				} 
			}
			if (bHeadshotHit)
			{
				if (ScoreManagerTimerSubSystem)
				{
					if (ScoreManagerTimerSubSystem->IsAccoladeTimerRunning(EAccolades::SkullNCrosshair))
						ScoreManagerTimerSubSystem->IncrementScullNCrosshairHeadshotHits();
					else
						ScoreManagerTimerSubSystem->StartAccoladeTimer(EAccolades::SkullNCrosshair);
				}
			}

			if (bPelletConnected)
			{
				ShowHitMarker();
				bPelletConnected = false;
			}

			if (OverheatAudioComp)
				OverheatAudioComp->SetPitchMultiplier((CurrentCharge / MaxChargeAmount));

			// Play gun sound
			if (GunShotAudioComp)
				GunShotAudioComp->Play();

			CurrentCharge += ShotCost;
			PlayWeaponCameraShake();

			// Call recoil
			if (RecoilComponent)
				RecoilComponent->RecoilKick();

			if (ScoreManagerSubSystem && EnemiesKilledFromAttack >= ScoreManagerSubSystem->GetBlunderBlastKillAmount())
			{
				if (ActorsKilledWhilePlayerAirborneIDs.Num() >= ScoreManagerSubSystem->GetBlunderBlastKillAmount())
					ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::DoubleAerialPlunder);
				if (ActorsKilledWhilePlayerGroundedIDs.Num() >= ScoreManagerSubSystem->GetDoubleAerialPlunderKillAmount())
					ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::BlunderBlast);
			}

			ActorsKilledWhilePlayerGroundedIDs.Empty();
			ActorsKilledWhilePlayerAirborneIDs.Empty();

			return true;
		}
	}
	return false;
}

void AShotgunWeapon::CheckIfAirborn(TArray<uint32> ActorsKilledWhilePlayerGroundedIDs,TArray<uint32> ActorsKilledWhilePlayerAirborneIDs, FHitResult HitResult)
{
	if (PlayerCharacter->GetMovementComponent()->IsMovingOnGround())
	{
		if (!ActorsKilledWhilePlayerGroundedIDs.Contains(HitResult.GetActor()->GetUniqueID()))
			ActorsKilledWhilePlayerGroundedIDs.AddUnique(HitResult.GetActor()->GetUniqueID());
	}
	else
	{
		if (!ActorsKilledWhilePlayerAirborneIDs.Contains(HitResult.GetActor()->GetUniqueID()))
		{
			ActorsKilledWhilePlayerAirborneIDs.AddUnique(HitResult.GetActor()->GetUniqueID());
			
			//Coin flip for voiceline
			if(FMath::RandRange(1,2) == 1)
				SoundManagerSubSystem->PlayPlayerSoundEvent(PlayerCharacter->PlayerVoiceAudioComp,6);
			else
				SoundManagerSubSystem->PlayNarratorSoundEvent(PlayerCharacter->PlayerVoiceAudioComp,2);
			SoundManagerSubSystem->PlayPlayerSoundEvent(PlayerCharacter->PlayerVoiceAudioComp,9);
		}
		
	}
}
