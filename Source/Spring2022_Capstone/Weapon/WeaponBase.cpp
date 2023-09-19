// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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
	//Sound Components
	GunShotAudioComp = CreateDefaultSubobject<UAudioComponent>("Gun Shot Audio");
	OverheatAudioComp = CreateDefaultSubobject<UAudioComponent>("Overheat Audio");
	GunChangeAudioComp = CreateDefaultSubobject<UAudioComponent>("GunSwitch Audio");
	
    OverheatAudioComp->bAutoActivate = false;
	GunShotAudioComp->bAutoActivate = false;
	GunChangeAudioComp->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	GunShotAudioComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	OverheatAudioComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	GunChangeAudioComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	OverheatAudioComp->SetSound(HeatBuildUp);
	
	PlayerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager; // No constructor will crash (execution order),
	
	// call CrystalCooldown() every second to recharge crystalCharge
	GetWorldTimerManager().SetTimer(ChargeCooldownTimerHandle, this,&AWeaponBase::ChargeCooldown, 1.0f, true, 2.0f);

	GetWorldTimerManager().ClearTimer(FireTimerHandle);

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)); 

	// DEBUG - attach weapon on spawn. Note - Requires weapons placed in level. - ToDo: Need creator/factory/manager to create and handle weapon instances.
	if(!PlayerCharacter->GetWeapon1())
	{
		PlayerCharacter->SetWeapon1(this);
		AttachWeapon(PlayerCharacter);
	}
	else if(!PlayerCharacter->GetWeapon2())
	{
		PlayerCharacter->SetWeapon2(this);
		AttachWeapon(PlayerCharacter);
	}

	ScoreManagerSubSystem = GetGameInstance()->GetSubsystem<UScoreSystemManagerSubSystem>();
	ScoreManagerTimerSubSystem = GetWorld()->GetSubsystem<UScoreSystemTimerSubSystem>();

	SoundManagerSubSystem = GetGameInstance()->GetSubsystem<USoundManagerSubSystem>();
	
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

void AWeaponBase::PlayTracerEffect(FVector TracerEndPoint)
{
	if(BulletTracerNiagaraSystem)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BulletTracerNiagaraSystem, SkeletalMesh->GetSocketLocation(ShootingStartSocket),
			FRotator::ZeroRotator)->SetVectorParameter("BeamEnd", TracerEndPoint);
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

float AWeaponBase::GetCurrentCharge() const
{
	return CurrentCharge;
}

void AWeaponBase::ChargeCooldown()
{
	if(CurrentCharge > 0 && bIsOverheating == false)
	{
		CurrentCharge -= ChargeCooldownRate;
	}

	if(CurrentCharge <= 0)
	{
		OverheatAudioComp->Stop();
	}
}

void AWeaponBase::Overheat()
{
	// GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("OVERHEATING"));
	bIsOverheating = true;
	TriggerEffect();
	bCanFire = false;

	if(OverheatAudioComp)
	{
		SoundManagerSubSystem->PlayPlayerSoundEvent(PlayerCharacter->PlayerVoiceAudioComp,8);
		OverheatAudioComp->SetSound(OverHeat);
		OverheatAudioComp->SetVolumeMultiplier(1.f);
		OverheatAudioComp->SetPitchMultiplier(1.f);
		OverheatAudioComp->Play();
	}

	// Play start & loop of overheat animation montage.
	PlayerCharacter->PlayOverheatMontage(false);
	
	GetWorldTimerManager().SetTimer(OverheatTimerHandle, this, &AWeaponBase::WeaponCooldown, OverheatTime, false, -1);

	// Check the status of the 'Hot Headed' accolade.
	if(ScoreManagerSubSystem)
		ScoreManagerSubSystem->CheckHotHeaded();
}

void AWeaponBase::WeaponCooldown()
{
	GetWorldTimerManager().ClearTimer(OverheatTimerHandle); 
	bIsOverheating = false;
	TriggerEffect();
	OverheatAudioComp->Stop();
	bCanFire = true;
	CurrentCharge = 0;
	
	OverheatAudioComp->SetSound(HeatBuildUp);
	OverheatAudioComp->Stop();

	// Play end of overheat montage.
	PlayerCharacter->PlayOverheatMontage(true);
	// GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("WEAPON COOLED"));
}

void AWeaponBase::ShowHitMarker()
{
	PlayerCharacter->ChangeCrosshair();
}

void AWeaponBase::AttachWeapon(APlayerCharacter* TargetCharacter)
{
	
	PlayerCharacter = TargetCharacter;

	if(PlayerCharacter == nullptr)
	{
		return;
	}

	// Attach the weapon to the Player PlayerCharacter
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true); 
	AttachToComponent(PlayerCharacter->GetMesh(), AttachmentRules, FName(WeaponSocketName));
	SetActorHiddenInGame(true);
	
}
