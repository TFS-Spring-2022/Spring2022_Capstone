// Created by Spring2022_Capstone team


#include "OutOfBoundsTriggerBox.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/Enemies/BaseEnemy.h"
#include "Spring2022_Capstone/Player/PlayerCharacter.h"


AOutOfBoundsTriggerBox::AOutOfBoundsTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AOutOfBoundsTriggerBox::OnOverlapBegin);
}

void AOutOfBoundsTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void AOutOfBoundsTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor->IsA(APlayerCharacter::StaticClass()))
		OtherActor->SetActorLocation(UGameplayStatics::GetGameMode(GetWorld())->FindPlayerStart(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->GetController())->GetActorLocation());
	else if(OtherActor->IsA(ABaseEnemy::StaticClass()))
		Cast<ABaseEnemy>(OtherActor)->DamageActor(this, 9999); // 'Kill' enemy if they manage to fall out of bounds.
}
