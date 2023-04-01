// Created by Spring2022_Capstone team

#include "RangedWeapon.h"

URangedWeapon::URangedWeapon()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
}

// Called when the game starts or when spawned
void URangedWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

