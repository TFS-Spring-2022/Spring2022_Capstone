// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DOTRadius.generated.h"
class USphereComponent;
UCLASS()
class SPRING2022_CAPSTONE_API ADOTRadius : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADOTRadius();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* SphereCollision;
	UPROPERTY(BlueprintReadWrite)
		TSet<AActor*> DamageActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		float DamagePerSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		float CloudSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		float Radius;

	UFUNCTION(BlueprintCallable)
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	
	UFUNCTION(BlueprintCallable)
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
