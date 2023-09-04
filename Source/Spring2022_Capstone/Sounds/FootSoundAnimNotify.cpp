// Created by Spring2022_Capstone team


#include "FootSoundAnimNotify.h"

#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Spring2022_Capstone/Spring2022_Capstone.h"

void UFootSoundAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	CheckGround(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference);
}

void UFootSoundAnimNotify::CheckGround(USkeletalMeshComponent* MeshComp)
{
	FHitResult HitResult;

	FVector StartTrace = MeshComp->GetComponentLocation();
	StartTrace.Z -= 10; // TEMP: Offset to make debug draw lines visible without moving.
	FVector DownVector = FVector(0,0,1);
	FVector EndTrace = ((DownVector * 150.f * -1) + StartTrace);
	FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
	TraceParams->bReturnPhysicalMaterial = true;  // Hit must return a physical material to tell if the player has hit a headshot.
	TraceParams->AddIgnoredComponent(MeshComp);
	DrawDebugLine(GetWorld(),StartTrace, EndTrace,FColor::Cyan,true,5.f,1.f);

	
			
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Turquoise,HitResult.PhysMaterial.Get()->GetName());
			EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
				if(CurrentGroundMat != Cast<UPhysicalMaterial>(HitResult.PhysMaterial.Get()))
				{
					CurrentGroundMat = Cast<UPhysicalMaterial>(HitResult.PhysMaterial.Get());
					switch (HitSurfaceType)
					{
					case SURFACE_Rock:
						if(RockStepSound)
						{
							Sound = RockStepSound;
							GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Rock");
						}
						break;
					case SURFACE_Wood:
						if(WoodStepSound)
						{
							Sound = WoodStepSound;
							GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Wood");
						}
						break;
					case SURFACE_Grass:
						if(GrassStepSound)
						{
							Sound = GrassStepSound;
							GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Grass");
						}
						break;
					case SURFACE_Water:
						if(WaterStepSound)
						{
							Sound = WaterStepSound;
							GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Water");
						}
						break;
					default:
						if(RockStepSound)
						{
							Sound = RockStepSound;
							GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Rock");
						}
						break;
					}
				}
		}
		
	
}
