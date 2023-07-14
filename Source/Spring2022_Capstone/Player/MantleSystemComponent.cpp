// Created by Spring2022_Capstone team


#include "MantleSystemComponent.h"

#include "PlayerCharacter.h"

// Sets default values for this component's properties
UMantleSystemComponent::UMantleSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UMantleSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayersCharacterMovementComponent = Cast<APlayerCharacter>(GetOwner())->GetCharacterMovement();
	
}


// Called every frame
void UMantleSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

