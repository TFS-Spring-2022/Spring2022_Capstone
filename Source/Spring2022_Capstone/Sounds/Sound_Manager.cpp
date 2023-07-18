// Created by Spring2022_Capstone team


#include "Sound_Manager.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASound_Manager::ASound_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASound_Manager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASound_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASound_Manager::PlaySound(FVector Location, USoundBase* Sound)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), "PlaySOund");
	if(Sound)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), "PlaySOundssss");
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location, 1.0f, 1.0f,0.0f);
	}
	
}



