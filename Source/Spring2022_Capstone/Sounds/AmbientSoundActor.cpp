// Created by Spring2022_Capstone team


#include "AmbientSoundActor.h"

#include "Sound/SoundNodeWavePlayer.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"

// Sets default values
AAmbientSoundActor::AAmbientSoundActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Trigger = CreateDefaultSubobject<USphereComponent>("Sphere Trigger");
	Trigger->SetGenerateOverlapEvents(true);
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Trigger->bHiddenInGame = false;
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio Component");
	AudioComponent->SetupAttachment(Trigger);
	AudioComponent->bAutoActivate = false;
	
	
}

// Called when the game starts or when spawned
void AAmbientSoundActor::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AAmbientSoundActor::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AAmbientSoundActor::OnOverlapEnd);
}

// Called every frame
void AAmbientSoundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmbientSoundActor::OnOverlapBegin(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		if(AudioComponent->Sound)
			{
				float RandomStartime = FMath::RandRange( 0.f , SoundDuration);
				GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Red,FString::SanitizeFloat(RandomStartime));
				AudioComponent->Play(RandomStartime);
			}
		}
}

void AAmbientSoundActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		
		
		GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Red, TEXT("Player is no longer within hear"));
		AudioComponent->Stop();
	}
	
}







