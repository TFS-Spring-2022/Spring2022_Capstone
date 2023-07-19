// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Spring2022_Capstone/Sounds/SoundManagerSubSystem.h"
#include "GrappleHook.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class SPRING2022_CAPSTONE_API AGrappleHook : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGrappleHook();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	FVector FireVelocity;
	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent *SphereCollider;
	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent *HookMesh;

	//Sounds
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* GrappleFireSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* GrappleRetractSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* GrappleHitSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	UAudioComponent* AudioComponent;

	UPROPERTY()
	USoundManagerSubSystem* SoundManagerSubSystem;

private:
	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	UProjectileMovementComponent *ProjectileMovementComp;
};
