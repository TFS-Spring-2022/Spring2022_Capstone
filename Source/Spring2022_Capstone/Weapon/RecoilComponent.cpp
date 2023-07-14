// Created by Spring2022_Capstone team


#include "RecoilComponent.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

URecoilComponent::URecoilComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URecoilComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningParentWeapon = Cast<AWeaponBase>(GetOwner()); 
	OwnersPlayerController = GetWorld()->GetFirstPlayerController();
	OwnersPawnMovementComponent = OwnersPlayerController->GetPawn()->GetMovementComponent();

	// Check if weapon has a 'larger' fire rate
	bHasLargerFireRate = (OwningParentWeapon->FireRate >= LargeFireRateSize) ? true : false;
	
	RecoilReset();
	
}

// Called when weapon is fired
void URecoilComponent::RecoilKick()
{

	// If first shot in batch, save Player's Control Rotation.
	if(bIsRecoiling == false)
		RecoilStartRotation = UKismetMathLibrary::NormalizedDeltaRotator(OwnersPlayerController->GetControlRotation(), FRotator::ZeroRotator);
	
	// Start timer to ensure RecoilStartRotation is not overwritten when firing multiple times.
	if(bHasLargerFireRate)
		// Weapon's with larger fire rates cannot use their FireRate to go into recovery, they must use LargeFireRateRecoveryStartTime.
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &URecoilComponent::FireTimerHandleFunction, LargeFireRateRecoveryStartTime, false);
	else
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &URecoilComponent::FireTimerHandleFunction, (OwningParentWeapon->FireRate + FireTimeBuffer), false);
	
	TimesFired++;

	// Knock up Player's Control Rotation.
	RecoilRotation = FRotator(OwnersPlayerController->GetControlRotation().Pitch - VerticalKickAmount, OwnersPlayerController->GetControlRotation().Yaw, OwnersPlayerController->GetControlRotation().Roll);
	OwnersPlayerController->SetControlRotation(RecoilRotation);

	// set bIsRecoiling true to calculate Player's mouse movement correction in TickComponent(). 
	bIsRecoiling = true;
	bIsRecovering = false;
}

void URecoilComponent::FireTimerHandleFunction()
{
	// Player has stopped firing, begin recovery.
	bIsRecoiling = false;
	bIsRecovering = true;
}

void URecoilComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(bIsRecoiling)
	{
		// Account for Player's mouse movement while weapon is recoiling.
		PitchRecoveryAmount = OwnersPlayerController->GetControlRotation().Pitch + (TimesFired * VerticalKickAmount);
		RecoveryRotation = FRotator(PitchRecoveryAmount, OwnersPlayerController->GetControlRotation().Yaw, OwnersPlayerController->GetControlRotation().Roll); /** Removing this FRotator and using PitchRecoveryAmount inside CorrectionRotation.Pitch will cause issues **/
	}
	else if(bIsRecovering)
	{
		// Set backup recovery timer to prevent control being taken from player.
		if(!GetWorld()->GetTimerManager().IsTimerActive(BackupRecoveryTimer))
			GetWorld()->GetTimerManager().SetTimer(BackupRecoveryTimer, this, &URecoilComponent::RecoilReset,  (bHasLargerFireRate) ? LargeFireRateMaxTimeInRecovery : OwningParentWeapon->FireRate + SemiAutomaticMaxTimeInRecoveryBuffer, false);

		RecoverRecoil(DeltaTime);
	}

	// Reset recoil when Player leaves the ground.
	if(!OwnersPawnMovementComponent->IsMovingOnGround())
		RecoilReset();
}

void URecoilComponent::RecoverRecoil(float Time)
{
	// If the Player is grounded and their aim has been knocked upwards
	if(OwnersPawnMovementComponent->IsMovingOnGround() && OwnersPlayerController->GetControlRotation().Pitch > RecoilStartRotation.Pitch)
	{
		// Reset the vertical recoil using RecoveryRotation calculated in bIsRecoiling, but maintain horizontal change.
		CorrectionRotation = UKismetMathLibrary::NormalizedDeltaRotator(FRotator(RecoveryRotation.Pitch, OwnersPlayerController->GetControlRotation().Yaw, OwnersPlayerController->GetControlRotation().Roll), FRotator::ZeroRotator); 
			
		// Bring down Player's Control Rotation to CorrectionRotation/RecoveryRotation.
		OwnersPlayerController->SetControlRotation(UKismetMathLibrary::RInterpTo(OwnersPlayerController->GetControlRotation(), CorrectionRotation, Time, RecoverySpeed));

		// Convert rotations to quaternions to ensure recoil recovers properly.
		FQuat CurrentRotationAsQuat = UKismetMathLibrary::NormalizedDeltaRotator(OwnersPlayerController->GetControlRotation(), FRotator::ZeroRotator).Quaternion();
		FQuat RecoveryTargetRotationAsQuat = UKismetMathLibrary::NormalizedDeltaRotator(FRotator(CorrectionRotation.Pitch, OwnersPlayerController->GetControlRotation().Yaw, OwnersPlayerController->GetControlRotation().Roll), FRotator::ZeroRotator).Quaternion();

		// When the Player's Control Rotation has recovered downwards enough, end recovery.	
		if(CurrentRotationAsQuat.Equals(RecoveryTargetRotationAsQuat, RecoilRecoveryTolerance))
			RecoilReset();
	}
	else
		RecoilReset();
}

void URecoilComponent::RecoilReset()
{
	bIsRecoiling = false;
	bIsRecovering = false;
	TimesFired = 0;
	
	RecoilRotation = FRotator::ZeroRotator;
	RecoveryRotation = FRotator::ZeroRotator;
	PitchRecoveryAmount = 0;

	GetWorld()->GetTimerManager().PauseTimer(BackupRecoveryTimer);
}
