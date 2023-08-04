// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "Engine.h"
//#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SniperEnemy.generated.h"



/**
 *
 */
UCLASS()
class SPRING2022_CAPSTONE_API ASniperEnemy : public ABaseEnemy
{
	GENERATED_BODY()




public:
	// Sets default values for this character's properties
	ASniperEnemy();

protected:
	virtual void Attack() override;

protected:

	void Raycast();

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
		int32 MagazineSize;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
		int32 Ammo;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
		float ReloadTime;
	float SniperDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
		float RotationSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
		float MaxRotationAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = true))
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = true))
		USkeletalMeshComponent* S_SniperEnemy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = true))
		USceneComponent* SniperRotation;

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedPrivateAccess = true))
		TSubclassOf<AActor> ActorToSpawn;
	
	void Reload();

	void Search();
};
