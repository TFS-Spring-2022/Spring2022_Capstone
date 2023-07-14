// Created by Spring2022_Capstone team


#include "SniperEnemy.h"
//#include "Runtime/Engine/Public/TimeManager.h"

ASniperEnemy::ASniperEnemy()
{
    /* PrimaryActorTick.bCanEverTick = true;

     Root = CreateDefaultSubobject<UScenceComponent>(Text"Sniper")
         SetRootComponent(Root);

     S_RangedEnemy = CreateDefaultSubobject<SkeletalMeshComponent>(Text("S_RangedEnemy"));
     S_RangedEnemy->SetupAttachment(Root);

     ReloadTime = 2.f;

     FTimerHandle ReloadTimeRanged; */
}

void ASniperEnemy::Attack()
{

}

void ASniper::Raycast()
{/*
    FHitResult* HitResult = new FHitResult();
    FVector StartTrace = WeaponMesh->GetComponentLocation;
    FVector ForwardVector = WeaponMesh->GetForwardVector;
    FVector EndTraceEditable = ((ForwardVector * RangedDistance, StartTrace)); //Changing the distance changes how far the raycast can go
    FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

    (GetWorld()->LineTraceSingleByChannel(StartTrace, EndTraceEditable, ECC_Visibility, *TraceParams))
        (
            DrawLine(GetWorld(), StartTrace, EndTraceEditable, FColor(255, 0, 0), false));


    if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTraceEditable, ECC_Visibility, *TraceParams))
        (
            DrawLine(GetWorld(), *HitResult, StartTrace, EndTraceEditable, FColor(255, 0, 0), True);
            FVector SpawnRangedHitLocation = *HitResult;
            FRotator SpawnRangedHitRotation = WeaponMesh->GetForwardVector;
            GetWorld()->SpawnActor<AActor(ActorToSpawn, SpawnRangedHitLocation, SpawnRangedHitRotation);
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::PrintF(TEXT("Sniper Raycast Hit Player")), *HitResult)));
            //EnemyMovementCheck = False;
            //My build lacked a base enemy rotating and looking around so code here is temporary I used the naming conventions for the code. With this I am hoping the base enemy has a bool for using
            //Whatever the code for moving the base enemy and it's rotation for shooting at the player,
            //this looking at the player and shooting can be set off. then movement and rotation of the player is turned back on with reload. Might end up being to simple here.
            GetWorld()->GetTimeManager().SetTimer(ReloadTimeRanged, this, Reload(), ReloadTime);
   */
}

void ASniperEnemy::Reload()
{
    // EnemyMovementCheck = True;
}


