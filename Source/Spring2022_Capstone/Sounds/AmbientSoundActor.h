// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundCue.h"
#include "AmbientSoundActor.generated.h"

UCLASS()
class SPRING2022_CAPSTONE_API AAmbientSoundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmbientSoundActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundCue* SoundCue;
	
	
	UPROPERTY(EditAnywhere, Category = Sounds)
	USphereComponent* Trigger;

	UPROPERTY()
	UAudioComponent* AudioComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
    
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
