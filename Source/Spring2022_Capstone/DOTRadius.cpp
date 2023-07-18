// Created by Spring2022_Capstone team


#include "DOTRadius.h"
#include "Spring2022_Capstone/HealthComponent.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
ADOTRadius::ADOTRadius() 
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	if (SphereCollision)
	{
		SphereCollision->SetupAttachment(RootComponent);
		SphereCollision->SetSphereRadius(1024.0f);
	}
	DamagePerSecond = 5;
	CloudSeconds = 15;
	Radius = 500;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADOTRadius::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{

	FDamageEvent DamageEvent;
}

void ADOTRadius::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{


}

// Called when the game starts or when spawned
void ADOTRadius::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADOTRadius::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	//for (AActor* Actor : DamageActors)
	//{
	//	Actor->TakeDamage(DamagePerSecond * DeltaTime, FDamageEvent(), nullptr, nullptr);
	//}
}

