// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify_PlaySound.h"
#include "Spring2022_Capstone/Enemies/BaseEnemy.h"
#include "LandSoundAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API ULandSoundAnimNotify : public UAnimNotify_PlaySound
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* WoodLandSound;
	
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* RockLandSound;
	
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* WaterLandSound;
	
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* GrassLandSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	UPhysicalMaterial* CurrentGroundMat;

	UPROPERTY()
	ABaseEnemy* EOwner;
	
	UFUNCTION()
	void CheckGround(USkeletalMeshComponent* MeshComp);

	UFUNCTION()
	void PlaySound(USkeletalMeshComponent* MeshComp) const;
};
