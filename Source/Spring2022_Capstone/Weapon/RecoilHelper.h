// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Components/ActorComponent.h"
#include "RecoilHelper.generated.h"

/// Handles AWeapon's recoil
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPRING2022_CAPSTONE_API URecoilHelper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecoilHelper();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(VisibleAnywhere)
	AWeaponBase* OwningParentWeapon; // Naming Parent or Owning?

	UPROPERTY(VisibleAnywhere)
	APlayerController* OwnersPlayerController;

	UPROPERTY(EditAnywhere)
	float VerticalKick;
	
};
