// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageArea.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS()
class SPRING2022_CAPSTONE_API ADamageArea : public AActor
{
	GENERATED_BODY()

public:
	ADamageArea();

	UFUNCTION(BlueprintCallable)
	void DamageActors();
	UFUNCTION(BlueprintCallable)
	void DestroyArea();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent *SphereCollider;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Damage;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float DamageInterval;
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Duration;
	
};
