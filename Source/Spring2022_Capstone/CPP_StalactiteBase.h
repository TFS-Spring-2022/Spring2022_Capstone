// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_StalactiteBase.generated.h"

UCLASS()
class SPRING2022_CAPSTONE_API ACPP_StalactiteBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_StalactiteBase();

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(BlueprintReadWrite)
		float MaxDamage;

	UPROPERTY(BlueprintReadWrite)
		int Multiplier;

	UPROPERTY(BlueprintReadWrite)
		float MaxPlayerSpeed;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
