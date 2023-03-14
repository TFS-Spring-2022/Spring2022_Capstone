// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BaseCharacter.h"
#include "WeaponBase.h"
#include "PickupBase.generated.h"

UCLASS()
class SPRING2022_CAPSTONE_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void CharacterPickedUp(ABaseCharacter* Character);


UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;

UPROPERTY(EditAnywhere)
	TSubclassOf<AWeaponBase> WeaponClass;
};
