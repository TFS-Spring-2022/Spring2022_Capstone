// Created by Spring2022_Capstone team


#include "Explosion.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AExplosion::AExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	Explode();
}

// Called every frame
void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosion::Explode()
{
	TArray<AActor*> HitActors;
	UKismetSystemLibrary::SphereOverlapActors(this, GetActorLocation(), Radius, ObjectTypes, AActor::StaticClass(), IgnoreActors, HitActors);
	
	for(int32 i = 0; i < HitActors.Num(); i++)
	{
		HitActors[i]->TakeDamage(Damage, FDamageEvent(),nullptr,nullptr);
	}
}
