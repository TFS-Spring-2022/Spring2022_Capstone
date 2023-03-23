// Created by Spring2022_Capstone team


#include "SemiAutomaticWeapon.h"


void ASemiAutomaticWeapon::Shoot()
{

	if(!bIsOverheating && CurWeaponCharge > 100 )
	{
		Overheat();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("OVERHEATING"));
	}
	
	if(bCanFire)
	{
		if(!GetWorldTimerManager().IsTimerActive(FireTimerHandle))							
		{	
			GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASemiAutomaticWeapon::ClearFireTimerHandle, FireRate, false);		// Start timer the fire rate timer (after it runs for FireRate (time between shots in seconds) it will be cleared

			FHitResult HitResult;

			FVector StartTrace = PlayerCamera->GetCameraLocation();
			FVector ForwardVector = PlayerCamera->GetActorForwardVector();
			FVector EndTrace = ((ForwardVector * 1000.0f) + StartTrace); // ToDo: Turn 1000.0f into a variable shot distance. Set it once we figure out level sizes.
			FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

			if(GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("PEW"));
				DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255,0,0), true);
			}

			CurWeaponCharge += ShotCost;
		}
	}
}
