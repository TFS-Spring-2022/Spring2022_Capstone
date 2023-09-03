// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "SoundManagerSubSystem.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Components/AudioComponent.h"
#include "FootAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API UFootAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
protected:
	bool isPaired = false;

	UPROPERTY()
	USoundManagerSubSystem* SoundManagerSubSystem;
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* FootStepsSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* LandingSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* WoodStepSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* WoodLandSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* RockStepSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* RockLandSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* WaterStepSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* WaterLandSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* GrassStepSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* GrassLandSound;
	

	UPROPERTY(EditAnywhere, Category = Sounds)
	UPhysicalMaterial* CurrentGroundMat;

	UFUNCTION()
	void CheckGround(USkeletalMeshComponent* MeshComp);
};
