// Created by Spring2022_Capstone team

#include "BaseEnemy.h"

#include "AIAttackSystemComponent.h"
#include "Spring2022_Capstone/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Spring2022_Capstone/Spring2022_CapstoneGameModeBase.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(WeaponMesh);

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentAttackSystemComponent = Cast<ASpring2022_CapstoneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetAttackSystemComponent();

	// Add enemy to AttackSystem Agents[] array on spawn.
	if(CurrentAttackSystemComponent)
		CurrentAttackSystemComponent->AddNewAgent(this);
}

void ABaseEnemy::Attack()
{
	if(bHasAttackToken)
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
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(this);

	// We want to hit the player's head as this is where the camera sits and will always hit the player if they can see the enemy (not behind cover)
	FHitResult PlayerHitResult;

	FVector StartPlayerAttackHitTrace = GetActorLocation(); // ProjectileSpawnPoint();
	FVector EndPlayerAttachHitTrace = PlayerCharacter->GetMesh()->GetBoneLocation("head"); // ToDo: const string HeadBone could be useful here once skeleton added

	DrawDebugLine(GetWorld(), StartPlayerAttackHitTrace, EndPlayerAttachHitTrace, FColor::Red, false, .5f);
	

	if(GetWorld()->LineTraceSingleByChannel(PlayerHitResult, StartPlayerAttackHitTrace, EndPlayerAttachHitTrace, ECC_Camera, *TraceParams))
	{
		DrawDebugLine(GetWorld(), StartPlayerAttackHitTrace, PlayerHitResult.Location, FColor::Red, false, .5f);
		
		if (PlayerHitResult.GetActor()->Implements<UDamageableActor>() && PlayerHitResult.GetActor()->IsA(APlayerCharacter::StaticClass())) // Question: Do we want them to be able to do damage to other enemies?
			Cast<APlayerCharacter>(PlayerHitResult.GetActor())->DamageActor(this, Damage);
	}
	
}

// Misses player and does no damage (called when player does not have token))
void ABaseEnemy::AttackMiss()
{
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(this);

	// We want to hit the player's head as this is where the camera sits and will always hit the player if they can see the enemy (not behind cover)
	FHitResult PlayerHitResult;

	FVector StartPlayerAttackHitTrace = GetActorLocation(); // ToDo: ProjectileSpawnPoint();
	FVector EndPlayerAttachHitTrace = PlayerCharacter->GetMesh()->GetBoneLocation("head"); // ToDo: const string HeadBone could be useful here once skeleton added
	EndPlayerAttachHitTrace.Z += 100;
	
	DrawDebugLine(GetWorld(), StartPlayerAttackHitTrace, EndPlayerAttachHitTrace, FColor::Black, false, .5f);

	// ToDo: Implement weighting missed shots into objects/player view
	if(GetWorld()->LineTraceSingleByChannel(PlayerHitResult, StartPlayerAttackHitTrace, EndPlayerAttachHitTrace, ECC_Camera, *TraceParams))
		DrawDebugLine(GetWorld(), StartPlayerAttackHitTrace, PlayerHitResult.Location, FColor::Black, false, .5f); 
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEnemy::DamageActor(AActor *DamagingActor, const float DamageAmount)
{
	IDamageableActor::DamageActor(DamagingActor, DamageAmount);
	if (HealthComp)
	{
		HealthComp->SetHealth(HealthComp->GetHealth() - DamageAmount);
		if(HealthComp->GetHealth() <= 0)
		{
			
			Death();
		}
	}
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

void ABaseEnemy::Death()
{

	// Drop Item
	for (const FEnemyDrop DroppableItem : Drops)
	{
		const float RandomValue = FMath::RandRange(0.0f, 100.0f);
		// If the drop chance is hit, spawn the drop and break loop.
		if(RandomValue < DroppableItem.DropChancePercentage)
		{
			const FVector DropLocation = GetActorLocation();
			const FRotator DropRotation = GetActorRotation();
			AActor* SpawnedPickup = GetWorld()->SpawnActor<ABasePickup>(DroppableItem.EnemyDrop, DropLocation, DropRotation);
			break;
		}
	}

	// ToDo: Rag doll enemy once new skeleton is implemented.
	ReleaseToken();
	if(CurrentAttackSystemComponent)
		CurrentAttackSystemComponent->RemoveAgent(this);
	UEnemyWaveManagementSystem* WaveManager = Cast<ASpring2022_CapstoneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetWaveManager();
	if(WaveManager)
		WaveManager->RemoveActiveEnemy(this);
	Destroy(false, true);
}

