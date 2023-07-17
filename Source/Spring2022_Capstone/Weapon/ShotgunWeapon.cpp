// Created by Spring2022_Capstone team


#include "ShotgunWeapon.h"
#include "DevTargets.h"
#include "Kismet/KismetMathLibrary.h"
#include "Spring2022_Capstone/GameplaySystems/PirateGameInstance.h"


AShotgunWeapon::AShotgunWeapon()
{
	RecoilComponent = CreateDefaultSubobject<URecoilComponent>("Shotgun Recoil Component");
}


void AShotgunWeapon::Shoot()
{

	if(!bIsOverheating && CurrentCharge > MaxChargeAmount )
	{
		Overheat();
	}
	
	if(bCanFire)
	{
		
		if(!GetWorldTimerManager().IsTimerActive(FireTimerHandle))							
		{
			// Start timer the fire rate timer (after it runs for FireRate (time between shots in seconds) it will be cleared
			GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AShotgunWeapon::ClearFireTimerHandle, FireRate, false);		

			FHitResult HitResult;

			FVector StartTrace = PlayerCamera->GetCameraLocation();
			StartTrace.Z -= 10; // TEMP: Offset to make debug draw lines visible without moving. 
			FVector ForwardVector = PlayerCamera->GetActorForwardVector();

			// ToDo: UPROPERTY IN HEADER (Naming and Degrees/Radians)	//
			float HalfAngle = 10;
			HalfAngle = UKismetMathLibrary::DegreesToRadians(HalfAngle);
			//															//
			
			for(int i = 0; i < PelletCount; i++)
			{
				
				// Get random direction inside cone projected from player
				ForwardVector = UKismetMathLibrary::RandomUnitVectorInConeInRadians(PlayerCamera->GetActorForwardVector(), HalfAngle);
				
				FVector EndTrace = ((ForwardVector * ShotDistance) + StartTrace);
				FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
				
				if(GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
				{
					if(HitResult.GetActor()->Implements<UDamageableActor>())
					{
						IDamageableActor* DamageableActor = Cast<IDamageableActor>(HitResult.GetActor());
						DamageableActor->DamageActor(this, ShotDamage);	
					}
					
					DrawDebugLine(GetWorld(), StartTrace, HitResult.Location, FColor::Black, false, 0.5f);
				}	
			}

			//Play gun sound
			
			
			
			CurrentCharge += ShotCost;
			PlayWeaponCameraShake();

			// Call recoil
			if(RecoilComponent)
				RecoilComponent->RecoilKick();
			
		}
	}
}



