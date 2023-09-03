// Created by Spring2022_Capstone team


#include "FootAnimNotify.h"
#include "Engine/GameEngine.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Spring2022_Capstone/Spring2022_Capstone.h"


void UFootAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if(!isPaired)
	{
		if(const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld()))
			SoundManagerSubSystem = GameInstance->GetSubsystem<USoundManagerSubSystem>();
		isPaired = true;
	}
	
	CheckGround(MeshComp);
	if(SoundManagerSubSystem)
	{
		if(FootStepsSound)
		SoundManagerSubSystem->PlaySound(MeshComp->GetComponentLocation(), FootStepsSound);
	}
}

void UFootAnimNotify::CheckGround(USkeletalMeshComponent* MeshComp)
	{
			FHitResult HitResult;

			FVector StartTrace = MeshComp->GetComponentLocation();
			StartTrace.Z -= 10; // TEMP: Offset to make debug draw lines visible without moving.
			FVector DownVector = FVector(0,0,1);
			FVector EndTrace = ((DownVector * 120.f * -1) + StartTrace);
			FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
			TraceParams->bReturnPhysicalMaterial = true;  // Hit must return a physical material to tell if the player has hit a headshot.
			TraceParams->AddIgnoredComponent(MeshComp);
			DrawDebugLine(GetWorld(),StartTrace,EndTrace,FColor::Purple);
			
			
			if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
			{
				//if(!isGrounded)
				//{
				//	LandingAudioComp->Play();
				//	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red, "We just Landed");
				//	isGrounded = true;
				//}
				EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
					if(CurrentGroundMat != Cast<UPhysicalMaterial>(HitResult.PhysMaterial.Get()))
					{
						CurrentGroundMat = Cast<UPhysicalMaterial>(HitResult.PhysMaterial.Get());
						switch (HitSurfaceType)
						{
						case SURFACE_Rock:
							if(RockStepSound)
							{
								FootStepsSound = RockStepSound;
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Rock");
							}
							if(RockLandSound)
							{
								LandingSound = RockLandSound;
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"LandSound is now Rock");
							}
							break;
						case SURFACE_Wood:
							if(WoodStepSound)
							{
								FootStepsSound = WoodStepSound;
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Wood");
							}
							if(WoodLandSound)
							{
								LandingSound = WoodLandSound;
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"LandSound is now Wood");
							}
							break;
						case SURFACE_Grass:
							if(GrassStepSound)
							{
								FootStepsSound = GrassStepSound;
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Grass");
							}
							if(GrassLandSound)
							{
								LandingSound = GrassLandSound;
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"LandSound is now Grass");
							}
							break;
						case SURFACE_Water:
							if(WaterStepSound)
							{
								FootStepsSound = WaterStepSound;
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Water");
							}
							if(WaterLandSound)
							{
								LandingSound = WaterLandSound;
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"LandSound is now Water");
							}
							break;
						default:
							if(RockStepSound)
							{
								FootStepsSound = RockStepSound;
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Rock");
							}
							if(RockLandSound)
							{
								LandingSound = RockLandSound;
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"LandSound is now Rock");
							}
							break;
						}
					}
			}
			//else
			//{
			//	if(isGrounded)
			//	{
			//		isGrounded = false;	
			//		FootStepAudioComp->Stop();
			//		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red, "We are not grounded");
			//	}
			//}
}