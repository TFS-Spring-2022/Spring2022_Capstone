// Created by Spring2022_Capstone team

#include "BaseEnemy.h"

#include "AIAttackSystemComponent.h"
#include "Spring2022_Capstone/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Spring2022_Capstone/Spring2022_CapstoneGameModeBase.h"
#include "Spring2022_Capstone/EnvironmentObjects/Hazards/Barrel.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(WeaponMesh);

	GunShotComp = CreateDefaultSubobject<UAudioComponent>(TEXT("GunAudioComp"));
	GunShotComp->SetupAttachment(WeaponMesh);
	VoiceAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Voice Audio"));
	VoiceAudioComponent->SetupAttachment(RootComponent);
	
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	NameTextRenderer = CreateDefaultSubobject<UTextRenderComponent>("Enemy Name Text");
	NameTextRenderer->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	NameTextRenderer->SetupAttachment(RootComponent);
	NameTextRenderer->SetRelativeLocation(FVector(0,0, GetDefaultHalfHeight() - NameTextRenderVerticalBuffer));
	NameTextRenderer->SetVisibility(false);
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Attach weapon to enemies hand socket
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	WeaponMesh->AttachToComponent(GetMesh(), AttachmentRules, WeaponSocket);
	GunShotComp->AttachToComponent(WeaponMesh, AttachmentRules);
	
	CurrentAttackSystemComponent = Cast<ASpring2022_CapstoneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetAttackSystemComponent();

	// Add enemy to AttackSystem Agents[] array on spawn.
	if (CurrentAttackSystemComponent)
		CurrentAttackSystemComponent->AddNewAgent(this);

	bIsFiring = false;

	if (!EnemyColors.IsEmpty())
		GetMesh()->SetMaterial(0, EnemyColors[FMath::RandRange(0, EnemyColors.Num() - 1)]);

	ScoreManagerSubSystem = GetGameInstance()->GetSubsystem<UScoreSystemManagerSubSystem>();
	ScoreManagerTimerSubSystem = GetWorld()->GetSubsystem<UScoreSystemTimerSubSystem>();
	SoundManagerSubSystem = GetGameInstance()->GetSubsystem<USoundManagerSubSystem>();
}

void ABaseEnemy::Attack()
{
	if (bHasAttackToken)
	{
		AttackHit();
		ReleaseToken();
	}
	else
		AttackMiss();

	
}

// Hits player and does damage (only called when enemy has token and then releases token)
void ABaseEnemy::AttackHit()
{
	bIsFiring = true; // Set false via Skeleton Notify in Pistol_Shoot_Powerful.

	FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(this);

	// We want to hit the player's head as this is where the camera sits and will always hit the player if they can see the enemy (not behind cover)
	FHitResult PlayerHitResult;

	FVector StartPlayerAttackHitTrace = GetActorLocation();								   // ProjectileSpawnPoint();
	FVector EndPlayerAttachHitTrace = PlayerCharacter->GetMesh()->GetBoneLocation("head"); // ToDo: const string HeadBone could be useful here once skeleton added

	DrawDebugLine(GetWorld(), StartPlayerAttackHitTrace, EndPlayerAttachHitTrace, FColor::Red, false, .5f);

	if (GetWorld()->LineTraceSingleByChannel(PlayerHitResult, StartPlayerAttackHitTrace, EndPlayerAttachHitTrace, ECC_Camera, *TraceParams))
	{
		DrawDebugLine(GetWorld(), StartPlayerAttackHitTrace, PlayerHitResult.Location, FColor::Red, false, .5f);

		if (PlayerHitResult.GetActor()->Implements<UDamageableActor>() && PlayerHitResult.GetActor()->IsA(APlayerCharacter::StaticClass())) // Question: Do we want them to be able to do damage to other enemies?
			Cast<APlayerCharacter>(PlayerHitResult.GetActor())->DamageActor(this, Damage);
	}
	if(!PlayerCharacter->isGrounded)
	{
		if(Cast<ASniperEnemy>(this))
			SoundManagerSubSystem->PlaySniperSoundEvent(VoiceAudioComponent,3);
		else
			SoundManagerSubSystem->PlayGruntSoundEvent(VoiceAudioComponent,0);
	}
	
	if(GunShotComp)
		GunShotComp->Play();
}

// Misses player and does no damage (called when player does not have token))
void ABaseEnemy::AttackMiss()
{
	bIsFiring = true; // Set false via Skeleton Notify in Pistol_Shoot_Powerful.

	FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(this);

	// We want to hit the player's head as this is where the camera sits and will always hit the player if they can see the enemy (not behind cover)
	FHitResult PlayerHitResult;

	FVector StartPlayerAttackHitTrace = GetActorLocation();								   // ToDo: ProjectileSpawnPoint();
	FVector EndPlayerAttachHitTrace = PlayerCharacter->GetMesh()->GetBoneLocation("head"); // ToDo: const string HeadBone could be useful here once skeleton added
	EndPlayerAttachHitTrace.Z += 100;

	DrawDebugLine(GetWorld(), StartPlayerAttackHitTrace, EndPlayerAttachHitTrace, FColor::Black, false, .5f);

	// ToDo: Implement weighting missed shots into objects/player view
	if (GetWorld()->LineTraceSingleByChannel(PlayerHitResult, StartPlayerAttackHitTrace, EndPlayerAttachHitTrace, ECC_Camera, *TraceParams))
		DrawDebugLine(GetWorld(), StartPlayerAttackHitTrace, PlayerHitResult.Location, FColor::Black, false, .5f);

	if(GunShotComp)
		GunShotComp->Play();

	SoundManagerSubSystem->PlayPlayerSoundEvent(PlayerCharacter->PlayerVoiceAudioComp,11);
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABaseEnemy::DamageActor(AActor *DamagingActor, const float DamageAmount, FName HitBoneName)
{

	if(bIsDying)
		return false;
	
	PlayHitAnimation(HitBoneName);

	if(Cast<ASniperEnemy>(this))
		SoundManagerSubSystem->PlaySniperSoundEvent(VoiceAudioComponent,1);
	else
		SoundManagerSubSystem->PlayGruntSoundEvent(VoiceAudioComponent,2);

	if(!Cast<ASniperEnemy>(this))
	{
		if(Cast<ABarrel>(DamagingActor))
			if(FMath::RandRange(1,2) == 1)
			{
				SoundManagerSubSystem->PlayGruntSoundEvent(VoiceAudioComponent,1);
			}
			else
			{
				SoundManagerSubSystem->PlayNarratorSoundEvent(PlayerCharacter->PlayerVoiceAudioComp, 10);
			}
	}
	
	IDamageableActor::DamageActor(DamagingActor, DamageAmount, HitBoneName);
	if (HealthComp)
	{
		if(HealthComp->GetHealth() > 0)
		{
			// Start Captains Coup Accolade Timer
			if(ScoreManagerTimerSubSystem && bIsElite)
				ScoreManagerTimerSubSystem->StartAccoladeTimer(EAccolades::CaptainsCoup);
			
			HealthComp->SetHealth(HealthComp->GetHealth() - DamageAmount);
			if (HealthComp->GetHealth() <= 0)
			{
				Death();
				return true;
			}
		}
		
	}
	return false;
}

void ABaseEnemy::ReceiveToken()
{
	IAttackSystemAgentInterface::ReceiveToken();
	bHasAttackToken = true;
}

void ABaseEnemy::ReleaseToken()
{
	IAttackSystemAgentInterface::ReleaseToken();
	CurrentAttackSystemComponent->ReturnToken();
	bHasAttackToken = false;
}

void ABaseEnemy::PromoteToElite()
{
	// Generate random name
	if(NameGenerator)
	{
		URandomNameGenerator* NameGeneratorInstance = NewObject<URandomNameGenerator>(this, NameGenerator);
		FText EliteName;
		
		if(FMath::RandBool())
			EliteName = NameGeneratorInstance->GetRandomFullName();
		else
			EliteName = FText::FromString(NameGeneratorInstance->GetRandomFirstName().ToString() + " " + NameGeneratorInstance->GetRandomLastName().ToString()); 
		
		NameTextRenderer->SetText(EliteName);
		NameTextRenderer->SetVisibility(true);
	}
	// Improve health.
	if(HealthComp)
	{
		const float NewMaxHealth = HealthComp->GetMaxHealth() * EliteMultiplier;
		HealthComp->SetMaxHealth(NewMaxHealth);
		HealthComp->SetHealth(NewMaxHealth);
	}
	// Improve damage.
	Damage *= EliteMultiplier;
	// Increase scale.
	SetActorRelativeScale3D(GetActorScale() * EliteMultiplier);
	// Create elite particles
	if(EliteParticleNiagaraSystem)
	{
		EliteParticleInstance = UNiagaraFunctionLibrary::SpawnSystemAttached(EliteParticleNiagaraSystem, GetMesh(), EliteParticleSocketName, FVector(0,0,0),
	FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true, true);
	}

	bIsElite = true;
	// ToDo: Play voice line.
}

void ABaseEnemy::Death() 
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("%s Killed"), *GetName()));
	// Prevent the shotgun from causing an enemy to call multiple Death multiple times.
	if(bIsDying)
		return;

	bIsDying = true;

	// Captains Coup Accolade
	if(bIsElite && ScoreManagerTimerSubSystem && ScoreManagerTimerSubSystem->IsAccoladeTimerRunning(EAccolades::CaptainsCoup))
	{
		ScoreManagerSubSystem->IncrementAccoladeCount(EAccolades::CaptainsCoup);
		ScoreManagerTimerSubSystem->StopAccoladeTimer(EAccolades::CaptainsCoup);
	}
	
	// Captain Of War Accolade
	if(ScoreManagerTimerSubSystem)
	{
		if(ScoreManagerTimerSubSystem->IsAccoladeTimerRunning(EAccolades::CaptainOfWar) == false)
			ScoreManagerTimerSubSystem->StartAccoladeTimer(EAccolades::CaptainOfWar);
		else
			ScoreManagerTimerSubSystem->IncrementCaptainOfWarKills();
	}
	
	if(GunShotComp)
	{
		GunShotComp->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		GunShotComp->DestroyComponent();
	}

	if(SoundManagerSubSystem)
	{
		if(Cast<ASniperEnemy>(this))
			SoundManagerSubSystem->PlaySniperSoundEvent(VoiceAudioComponent,2);
		else
			SoundManagerSubSystem->PlayGruntSoundEvent(VoiceAudioComponent,5);
	}
	
	if(!bIsElite)
	{
		// Drop health pack
		for (const FEnemyDrop DroppableItem : Drops)
		{
			const float RandomValue = FMath::RandRange(0.0f, 100.0f);
			// If the drop chance is hit, spawn the drop and break loop.
			if (RandomValue < DroppableItem.DropChancePercentage)
			{
				const FVector DropLocation = GetActorLocation();
				const FRotator DropRotation = GetActorRotation();
				AActor *SpawnedPickup = GetWorld()->SpawnActor<ABasePickup>(DroppableItem.EnemyDrop, DropLocation, DropRotation);
				break;
			}
		}
	}
	else
	{
		if(SniperDisableDropBP)
		{
			const FVector DropLocation = GetActorLocation();
			const FRotator DropRotation = GetActorRotation();
			AActor *SpawnedPickup = GetWorld()->SpawnActor<ASniperDisablePickup>(SniperDisableDropBP, DropLocation, DropRotation);
		}
	}


	// ToDo: Rag doll enemy once new skeleton is implemented.
	ReleaseToken();
	if (CurrentAttackSystemComponent)
		CurrentAttackSystemComponent->RemoveAgent(this);
	UEnemyWaveManagementSystem *WaveManager = Cast<ASpring2022_CapstoneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetWaveManager();
	if (WaveManager)
		WaveManager->RemoveActiveEnemy(this);

	// Ragdoll Enemy
	GetMesh()->SetSimulatePhysics(true);
	GetCapsuleComponent()->DestroyComponent();
	GetMesh()->SetCollisionProfileName("SkyPirateRagdoll");

	// Disable elite effects.
	NameTextRenderer->SetVisibility(false);
	if(EliteParticleInstance)
		EliteParticleInstance->DestroyInstance();

	if(ScoreManagerSubSystem)
	{
		ScoreManagerSubSystem->IncrementScoreCounter(EScoreCounters::EnemiesKilled);
		if(bIsElite)
			ScoreManagerSubSystem->IncrementScoreCounter(EScoreCounters::ElitesKilled);
	}
	
	// Note: Enemies are destroyed in EnemyWaveManagementSystem.
}
