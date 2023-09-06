// Created by Spring2022_Capstone team

#include "Kismet/GameplayStatics.h"
#include "LandSoundAnimNotify.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Spring2022_Capstone/Spring2022_Capstone.h"

void ULandSoundAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	CheckGround(MeshComp);
	PlaySound(MeshComp);
	
}

void ULandSoundAnimNotify::CheckGround(USkeletalMeshComponent* MeshComp)
{
	FVector StartTrace = MeshComp->GetBoneLocation(AttachName);
	FVector DownVector = FVector(0,0,1);
	FVector EndTrace = ((DownVector * 150.f * -1) + StartTrace);
	FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
	TraceParams->bReturnPhysicalMaterial = true;
	TraceParams->AddIgnoredComponent(MeshComp);
	
		
	DrawDebugLine(MeshComp->GetOwner()->GetWorld(),StartTrace, EndTrace,FColor::Cyan,true,5.f,0.f,5.f);

	
			
	if (FHitResult HitResult; MeshComp->GetOwner()->GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
			EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
				if(CurrentGroundMat != Cast<UPhysicalMaterial>(HitResult.PhysMaterial.Get()))
				{
					CurrentGroundMat = Cast<UPhysicalMaterial>(HitResult.PhysMaterial.Get());
					switch (HitSurfaceType)
					{
					case SURFACE_Rock:
						if(RockLandSound)
						{
							if(Cast<ABaseEnemy>(MeshComp->GetOwner()))
								Cast<ABaseEnemy>(MeshComp->GetOwner())->LandSound = RockLandSound;
						}
						break;
					case SURFACE_Wood:
						if(WoodLandSound)
						{
							if(Cast<ABaseEnemy>(MeshComp->GetOwner()))
								Cast<ABaseEnemy>(MeshComp->GetOwner())->LandSound = WoodLandSound;
						}
						break;
					case SURFACE_Grass:
						if(GrassLandSound)
						{
							if(Cast<ABaseEnemy>(MeshComp->GetOwner()))
								Cast<ABaseEnemy>(MeshComp->GetOwner())->LandSound = GrassLandSound;
						}
						break;
					case SURFACE_Water:
						if(WaterLandSound)
						{
							if(Cast<ABaseEnemy>(MeshComp->GetOwner()))
								Cast<ABaseEnemy>(MeshComp->GetOwner())->LandSound = WaterLandSound;
						}
						break;
					default:
						if(RockLandSound)
						{
							if(Cast<ABaseEnemy>(MeshComp->GetOwner()))
								Cast<ABaseEnemy>(MeshComp->GetOwner())->LandSound = RockLandSound;
						}
						break;
					}
				}
		}
		
	
}

void ULandSoundAnimNotify::PlaySound(USkeletalMeshComponent* MeshComp) const
{
	if (Sound && MeshComp)
	{
#if WITH_EDITORONLY_DATA
		if (const UWorld* World = MeshComp->GetWorld(); bPreviewIgnoreAttenuation && World && World->WorldType == EWorldType::EditorPreview)
		{
			UGameplayStatics::PlaySound2D(World, Sound, VolumeMultiplier, PitchMultiplier);
		}
		else
#endif
		{
			if (bFollow)
			{
				if(Cast<ABaseEnemy>(MeshComp->GetOwner())->LandSound)
					UGameplayStatics::SpawnSoundAttached(Cast<ABaseEnemy>(MeshComp->GetOwner())->LandSound, MeshComp, AttachName, FVector(ForceInit), EAttachLocation::SnapToTarget, false, VolumeMultiplier, PitchMultiplier);
			}
			else
			{
				if(Cast<ABaseEnemy>(MeshComp->GetOwner())->LandSound)
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), Cast<ABaseEnemy>(MeshComp->GetOwner())->LandSound, MeshComp->GetComponentLocation(), VolumeMultiplier, PitchMultiplier);
			}
		}
	}
}