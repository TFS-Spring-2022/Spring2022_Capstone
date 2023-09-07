// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify_PlaySound.h"
#include "Spring2022_Capstone/Enemies/BaseEnemy.h"
#include "FootSoundAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API UFootSoundAnimNotify : public UAnimNotify_PlaySound
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* WoodStepSound;
	
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* RockStepSound;
	
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* WaterStepSound;
	
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* GrassStepSound;
	
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* SandStepSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	UPhysicalMaterial* CurrentGroundMat;

	UPROPERTY()
	ABaseEnemy* EOwner;
	
	UFUNCTION()
	void CheckGround(USkeletalMeshComponent* MeshComp);

	UFUNCTION()
	void PlaySound(USkeletalMeshComponent* MeshComp) const;
};
