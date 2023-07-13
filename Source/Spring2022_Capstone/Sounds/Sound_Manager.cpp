// Created by Spring2022_Capstone team


#include "Sound_Manager.h"

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

