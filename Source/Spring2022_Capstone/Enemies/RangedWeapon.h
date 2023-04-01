// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RangedWeapon.generated.h"

UCLASS()
class SPRING2022_CAPSTONE_API URangedWeapon : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	URangedWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent *WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Damage;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float AttackSpeed;
};
