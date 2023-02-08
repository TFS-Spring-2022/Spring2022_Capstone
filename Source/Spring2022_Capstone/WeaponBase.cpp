// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh Component");

	RootComponent = SkeletalMesh;
	
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager; // No constructor will crash (execution order),
	
	// call CrystalCooldown() every second to recharge crystalCharge
	GetWorldTimerManager().SetTimer(ChargeCooldownTimerHandle, this,&AWeaponBase::ChargeCooldown, 1.0f, true, 2.0f);

	GetWorldTimerManager().ClearTimer(FireTimerHandle); 
	
}

// QUESTION: Trust Garbage Collection or manually clear timers in destructor?
void AWeaponBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// ToDo: Change shot location start from camera to barrel.
void AWeaponBase::RaycastFire()
{
	
	if(!bIsOverheating && CurWeaponCharge > 100 )
	{
		Overheat();
	}
	
	if(bCanFire)
	{
		if(!GetWorldTimerManager().IsTimerActive(FireTimerHandle))							
		{	
			GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AWeaponBase::ClearFireTimerHandle, FireRate, false);		// Start timer the fire rate timer (after it runs for FireRate (time between shots in seconds) it will be cleared

			FHitResult HitResult;

			FVector StartTrace = PlayerCamera->GetCameraLocation();
			FVector ForwardVector = PlayerCamera->GetActorForwardVector();
			FVector EndTrace = ((ForwardVector * 1000.0f) + StartTrace); // ToDo: Turn 1000.0f into a variable shot distance. Set it once we figure out level sizes.
			FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

			if(GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
			{
				DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255,0,0), true);
			}

			CurWeaponCharge += ShotCost;
		}
	}
}

void AWeaponBase::ClearFireTimerHandle()
{
	GetWorldTimerManager().ClearTimer(FireTimerHandle); 
}

void AWeaponBase::ChargeCooldown()
{
	if(CurWeaponCharge < 100)
	{
		CurWeaponCharge -= ChargeCooldownRate;
	}
}

void AWeaponBase::Overheat()
{
	bIsOverheating = true;
	bCanFire = false;
	
	GetWorldTimerManager().SetTimer(OverheatTimerHandle, this, &AWeaponBase::WeaponCooldown, OverheatTime, false, -1);
}

void AWeaponBase::WeaponCooldown()
{
	GetWorldTimerManager().ClearTimer(OverheatTimerHandle); 
	bIsOverheating = false;
	bCanFire = true;
}
