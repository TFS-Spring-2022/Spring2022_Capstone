// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageArea.generated.h"

class USphereComponent;

UCLASS()
class SPRING2022_CAPSTONE_API ADamageArea : public AActor
{
	GENERATED_BODY()
	
public:
	ADamageArea();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent *SphereCollider;

};
