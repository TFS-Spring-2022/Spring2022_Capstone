// Created by Spring2022_Capstone team


#include "NotificationUIManager.h"

// Sets default values
ANotificationUIManager::ANotificationUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // can probably be false

}

// Called when the game starts or when spawned
void ANotificationUIManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANotificationUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

