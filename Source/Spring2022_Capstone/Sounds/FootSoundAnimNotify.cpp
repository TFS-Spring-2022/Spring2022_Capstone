// Created by Spring2022_Capstone team


#include "FootSoundAnimNotify.h"

#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include  "Engine/World.h"
#include "Spring2022_Capstone/Spring2022_Capstone.h"

void UFootSoundAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	CheckGround(MeshComp);
	PlaySound(MeshComp);
	
}

void UFootSoundAnimNotify::CheckGround(USkeletalMeshComponent* MeshComp)
{
	FVector StartTrace = MeshComp->GetBoneLocation(AttachName);
	FVector DownVector = FVector(0,0,1);
	FVector EndTrace = ((DownVector * 10.f * -1) + StartTrace);
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
						if(RockStepSound)
						{
							if(Cast<ABaseEnemy>(MeshComp->GetOwner()))
								Cast<ABaseEnemy>(MeshComp->GetOwner())->FootStepSound = RockStepSound;
						}
						break;
					case SURFACE_Wood:
						if(WoodStepSound)
						{
							if(Cast<ABaseEnemy>(MeshComp->GetOwner()))
								Cast<ABaseEnemy>(MeshComp->GetOwner())->FootStepSound = WoodStepSound;
						}
						break;
					case SURFACE_Grass:
						if(GrassStepSound)
						{
							if(Cast<ABaseEnemy>(MeshComp->GetOwner()))
								Cast<ABaseEnemy>(MeshComp->GetOwner())->FootStepSound = GrassStepSound;
						}
						break;
					case SURFACE_Water:
						if(WaterStepSound)
						{
							if(Cast<ABaseEnemy>(MeshComp->GetOwner()))
								Cast<ABaseEnemy>(MeshComp->GetOwner())->FootStepSound = WaterStepSound;
						}
						break;
					default:
						if(RockStepSound)
						{
							if(Cast<ABaseEnemy>(MeshComp->GetOwner()))
								Cast<ABaseEnemy>(MeshComp->GetOwner())->FootStepSound = RockStepSound;
						}
						break;
					}
				}
		}
		
	
}

void UFootSoundAnimNotify::PlaySound(USkeletalMeshComponent* MeshComp) const
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
				if(Cast<ABaseEnemy>(MeshComp->GetOwner())->FootStepSound)
				UGameplayStatics::SpawnSoundAttached(Cast<ABaseEnemy>(MeshComp->GetOwner())->FootStepSound, MeshComp, AttachName, FVector(ForceInit), EAttachLocation::SnapToTarget, false, VolumeMultiplier, PitchMultiplier);
			}
			else
			{
				if(Cast<ABaseEnemy>(MeshComp->GetOwner())->FootStepSound)
				UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), Cast<ABaseEnemy>(MeshComp->GetOwner())->FootStepSound, MeshComp->GetComponentLocation(), VolumeMultiplier, PitchMultiplier);
			}
		}
	}
}
