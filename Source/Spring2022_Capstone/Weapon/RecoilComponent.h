// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Components/ActorComponent.h"
#include "RecoilComponent.generated.h"

/// Handles recoil for parent weapons.
/// @warning - Can only be added to AWeaponBase and children. 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Within=(WeaponBase))
class SPRING2022_CAPSTONE_API URecoilComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecoilComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	/**
	 * @brief WeaponBase the RecoilComponent is attached to. 
	 */
	AWeaponBase* OwningParentWeapon; 
	
	APlayerController* OwnersPlayerController;
	
};
