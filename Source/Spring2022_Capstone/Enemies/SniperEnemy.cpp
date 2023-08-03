// Created by Spring2022_Capstone team


#include "SniperEnemy.h"
#include "Kismet/KismetMathLibrary.h"
//#include "Runtime/Engine/Public/TimeManager.h"

ASniperEnemy::ASniperEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(FName("Sniper"));
         SetRootComponent(Root);

     S_SniperEnemy = CreateDefaultSubobject<USkeletalMeshComponent>(FName("S_SniperEnemy"));
     S_SniperEnemy->SetupAttachment(Root);

     ReloadTime = 2.f;
     SniperDistance = 10000;
     RotationSpeed = 5.f;
     MaxRotationAngle = 100.f;

     SniperRotation = CreateDefaultSubobject<USceneComponent>(FName("SniperEnemy_RotationComponent"));
     SniperRotation->SetupAttachment(Root);
}

void ASniperEnemy::Attack()
{
    
}

void ASniperEnemy::Search()
{

    float RotationAngle = FMath::Sin(GetWorld()->GetTimeSeconds() * RotationSpeed * PI / 180.0f) * MaxRotationAngle;

    FRotator Rotation = GetActorRotation();
    Rotation.Yaw += RotationAngle;
    SetActorRotation(Rotation);
}

void ASniperEnemy::Raycast()
{
    
    FHitResult* HitResult = new FHitResult();
    FVector StartTrace = ProjectileSpawnPoint->GetComponentLocation(); 
    FVector ForwardVector = ProjectileSpawnPoint->GetForwardVector();
    FVector EndTraceEditable = ((ForwardVector * SniperDistance, StartTrace)); //Changing the distance changes how far the raycast can go
    FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
   
   /* GetWorld()->LineTraceSingleByChannel(StartTrace, EndTraceEditable, ECC_Visibility, *TraceParams))
        (
            DrawLine(GetWorld(), StartTrace, EndTraceEditable, FColor(255, 0, 0), false));
    */
    DrawDebugLine(GetWorld(), StartTrace, EndTraceEditable, FColor(255, 0, 0), false, -1, 0, 10.0f); //I was unable to get the nonedebug working in time so hade it swithc to this

    

    if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTraceEditable, ECC_Visibility, *TraceParams))
    {
        //DrawLine(GetWorld(), *HitResult, StartTrace, EndTraceEditable, FColor(255, 0, 0), True); currently not functional
        FVector SpawnSniperHitLocation = HitResult->Location;
        FRotator SpawnSniperHitRotation = UKismetMathLibrary::MakeRotFromX(ProjectileSpawnPoint->GetForwardVector());
        GetWorld()->SpawnActor <AActor>(ActorToSpawn, SpawnSniperHitLocation, SpawnSniperHitRotation);
    }
   
}

void ASniperEnemy::Reload()
{
    // EnemyMovementCheck = True;
}
/*
//This is other code I am trying out for what I haven't completed
Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::PrintF(TEXT("Sniper Raycast Hit Player")), *HitResult)));
          EnemyMovementCheck = False;
         // Still working on the freeze. My build lacked a base enemy rotating and looking around so code here is temporary I used the naming conventions for the code. With this I am hoping the base enemy has a bool for using
        //  Whatever the code for moving the base enemy and it's rotation for shooting at the player,
         //this looking at the player and shooting can be set off. then movement and rotation of the player is turned back on with reload. Might end up being to simple here.
          GetWorld()->GetTimeManager().SetTimer(ReloadTimeRanged, this, Reload(), ReloadTime);
          */