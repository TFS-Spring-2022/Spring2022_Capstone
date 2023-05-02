// Created by Spring2022_Capstone team


#include "SemiAutomaticWeapon.h"

#include "DevTargets.h"


ASemiAutomaticWeapon::ASemiAutomaticWeapon()
{

	RecoilComponent = CreateDefaultSubobject<URecoilComponent>("SemiAuto Recoil Component");
	
}

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
			// Start timer the fire rate timer (after it runs for FireRate (time between shots in seconds) it will be cleared
			GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASemiAutomaticWeapon::ClearFireTimerHandle, FireRate, false);		

			FHitResult HitResult;

			FVector StartTrace = PlayerCamera->GetCameraLocation();
			StartTrace.Z -= 10; // TEMP: Offset to make debug draw lines visible without moving. 
			FVector ForwardVector = PlayerCamera->GetActorForwardVector();
			FVector EndTrace = ((ForwardVector * ShotDistance) + StartTrace); 
			FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

			if(GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
			{
				if(HitResult.GetActor()->IsA(ADevTargets::StaticClass()))
				{
					ADevTargets* CurrentHit = Cast<ADevTargets>(HitResult.GetActor());
					CurrentHit->ToggleMaterial();
				}
				DrawDebugLine(GetWorld(), StartTrace, HitResult.Location, FColor::Black, false, 0.5f);
			}
			
			CurWeaponCharge += ShotCost;

			// Call recoil
			if(RecoilComponent)
			{
				RecoilComponent->RecoilStart();
			}
				
		}
	}
}
