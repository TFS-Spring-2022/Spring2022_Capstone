// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Spring2022_Capstone/Sounds/Sound_Manager.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

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

	Character = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)); 

	// DEBUG - attach weapon on spawn. Note - Requires weapons placed in level. - ToDo: Need creator/factory/manager to create and handle weapon instances.
	if(!Character->GetWeapon1())
	{
		Character->SetWeapon1(this);
		AttachWeapon(Character);
	}
	else if(!Character->GetWeapon2())
	{
		Character->SetWeapon2(this);
		AttachWeapon(Character);
	}

	//Get Game mode instance
	SkyPirateGameMode = Cast<ASkyPirateGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(SkyPirateGameMode)
	{
		 SoundManagerInstance = SkyPirateGameMode->GetSoundManager();
	}
	
	
}

void AWeaponBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void AWeaponBase::PlayWeaponCameraShake()
{
	if(FireCameraShake)
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(FireCameraShake);
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AWeaponBase::GetDamage()
{
    return ShotDamage;
}

void AWeaponBase::SetDamage(float Value)
{
	ShotDamage = Value;
}

void AWeaponBase::ClearFireTimerHandle()
{
	GetWorldTimerManager().ClearTimer(FireTimerHandle); 
}

void AWeaponBase::ChargeCooldown()
{
	if(CurrentCharge > 0 && bIsOverheating == false)
	{
		CurrentCharge -= ChargeCooldownRate;
	}
}

void AWeaponBase::Overheat()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("OVERHEATING"));
	bIsOverheating = true;
	bCanFire = false;
	
	GetWorldTimerManager().SetTimer(OverheatTimerHandle, this, &AWeaponBase::WeaponCooldown, OverheatTime, false, -1);
}

void AWeaponBase::WeaponCooldown()
{
	GetWorldTimerManager().ClearTimer(OverheatTimerHandle); 
	bIsOverheating = false;
	bCanFire = true;
	CurrentCharge = 0;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("WEAPON COOLED"));
}

void AWeaponBase::AttachWeapon(APlayerCharacter* TargetCharacter)
{
	
	Character = TargetCharacter; 

	if(Character == nullptr)
	{
		return;
	}

	// Attach the weapon to the Player Character
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true); 
	// ToDo: Connect to skeletal mesh when it is added.
	//AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	AttachToComponent(Character->GetRootComponent(), AttachmentRules, FName(TEXT("GripPoint"))); // ToDo: SkeletonMesh and Socket
	
}
