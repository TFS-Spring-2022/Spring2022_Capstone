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
class SPRING2022_CAPSTONE_API ASniper : public ABaseEnemy
{
	GENERATED_BODY()




public:
	// Sets default values for this character's properties
	ASniperEnemy();

protected:
	virtual void Attack() override;

private:

	void Raycast();

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
		int MagazineSize;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
		int Ammo;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
		float ReloadTime;
	float RangeDistance;

	UPROPERTY(EditAnywhere, meta = (AllowedPrivateAccess = True))
		TSubclassOf<AActor> ActorToSpawn;
	void Reload();
};
