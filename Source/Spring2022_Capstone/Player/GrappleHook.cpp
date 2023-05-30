// Created by Spring2022_Capstone team

#include "GrappleHook.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AGrappleHook::AGrappleHook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HookMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HookMesh"));
	RootComponent = HookMesh;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("GrappleCollider"));
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->SetSimulatePhysics(false);
	SphereCollider->SetNotifyRigidBodyCollision(true);
	SphereCollider->SetWorldScale3D(FVector(2, 2, 2));

	SphereCollider->BodyInstance.SetCollisionProfileName("BlockAllDynamic");

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->ProjectileGravityScale = 0;

}

// Called when the game starts or when spawned
void AGrappleHook::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovementComp->SetVelocityInLocalSpace(FireVelocity);
}

// Called every frame
void AGrappleHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

