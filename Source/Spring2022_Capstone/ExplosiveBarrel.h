// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spring2022_Capstone/GameplaySystems/DamageableActor.h"
#include "ExplosiveBarrel.generated.h"

UCLASS()
class SPRING2022_CAPSTONE_API AExplosiveBarrel : public AActor, public IDamageableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void DamageActor(AActor* DamagingActor, const float DamageAmount) override;

	UFUNCTION(BlueprintImplementableEvent)
	void DamageActorBP();
};
