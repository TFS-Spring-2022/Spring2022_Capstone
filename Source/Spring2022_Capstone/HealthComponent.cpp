// Created by Spring2022_Capstone team

#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	HealthPoints = MaxHealth;
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UHealthComponent::GetHealth()
{
    return HealthPoints;
}

void UHealthComponent::SetHealth(float NewHealth)
{
	if (NewHealth > MaxHealth)
	{
		NewHealth = MaxHealth;
	}
	HealthPoints = NewHealth;
}

float UHealthComponent::GetMaxHealth()
{
    return MaxHealth;
}

void UHealthComponent::SetMaxHealth(float value)
{
    MaxHealth = value;
}
