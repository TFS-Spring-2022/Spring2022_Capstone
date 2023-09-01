// Created by Spring2022_Capstone team

#include "PlayerCharacter.h"
#include "GrappleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GrappleState.h"
#include "MantleSystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Spring2022_Capstone/Weapon/WeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Spring2022_Capstone/HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Spring2022_Capstone/Spring2022_Capstone.h"
#include "Spring2022_Capstone/Spring2022_CapstoneGameModeBase.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	Camera->bUsePawnControlRotation = true;

	// Rotate with controller's pitch so player's arms/weapons move vertically.
	bUseControllerRotationPitch = true;
	
	GrappleComponent = CreateDefaultSubobject<UGrappleComponent>(TEXT("Grapple"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	UpgradeSystemComponent = CreateDefaultSubobject<UUpgradeSystemComponent>("Upgrades System");

	PlayerMantleSystemComponent = CreateDefaultSubobject<UMantleSystemComponent>(TEXT("Mantle"));

	FootStepAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Foot Steps"));
	LandingAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Landing Steps"));

	CrouchEyeOffset = FVector(0.f);
	CrouchSpeed = 12.f;

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Dash);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(GrappleAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Grapple);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Crouch);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
		EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Completed, this,
										   &APlayerCharacter::SwitchWeapon);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Sprint);
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	SoundManagerSubSystem = GameInstance->GetSubsystem<USoundManagerSubSystem>();

	FootStepAudioComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	LandingAudioComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CheckGround();
	
	if (APlayerController *PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<
				UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CharacterMappingContext, 0);
		}
	}
	Speed = GetCharacterMovement()->MaxWalkSpeed;
	UpdateHealthBar();

	bIsMantleing = false;

	// Create and add Player HUD
	if(PlayerHUDWidgetBP)
	{
		PlayerHUDWidgetInstance = Cast<UHUDWidget>(CreateWidget(GetWorld(), PlayerHUDWidgetBP));
		PlayerHUDWidgetInstance->AddToViewport(1);
	}
	// Create and add Damage Indicator Widget
	if(DamageIndicatorWidgetBP)
	{
		DirectionalDamageIndicatorWidget = Cast<UDirectionalDamageIndicatorWidget>(CreateWidget(GetWorld(), DamageIndicatorWidgetBP));
		DirectionalDamageIndicatorWidget->AddToViewport(1);
	}
	
	bDashBlurFadingIn = false;
	CurrentGameMode = Cast<ASpring2022_CapstoneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));


	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController(), false);

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float CrouchInterpTime = FMath::Min(1.f, CrouchSpeed * DeltaTime);
	CrouchEyeOffset = (1.f - CrouchInterpTime) * CrouchEyeOffset;
	CheckGround();

	if(bDashBlurFadingIn)
		Camera->PostProcessSettings.WeightedBlendables.Array[0].Weight = FMath::FInterpTo(Camera->PostProcessSettings.WeightedBlendables.Array[0].Weight, 1, DeltaTime, DASH_BLUR_FADEIN_SPEED);
	
}

void APlayerCharacter::Move(const FInputActionValue &Value)
{
	const FVector2D DirectionalValue = Value.Get<FVector2D>();
	if (GetController() && (DirectionalValue.X != 0.f || DirectionalValue.Y != 0.f))
	{
		bIsMoving = true;
		GetCharacterMovement()->MaxWalkSpeed = bIsSprinting ? Speed * SprintMultiplier : Speed;
		AddMovementInput(GetActorForwardVector(), DirectionalValue.Y * 100);
		AddMovementInput(GetActorRightVector(), DirectionalValue.X * 100);
	}
	else
		bIsMoving = false;
}

void APlayerCharacter::Jump()
{
	
	if(!bIsMantleing)
	{
		if(bIsMoving)
		{
			if(PlayerMantleSystemComponent->AttemptMantle())
			{
				if(SoundManagerSubSystem)
				{
					SoundManagerSubSystem->PlaySound(this->GetActorLocation(), MantleSC);
				}
				bIsMantleing = true;
				return;
			}
		}
	}

	Super::Jump();
}

void APlayerCharacter::Dash(const FInputActionValue &Value)
{
	const float CurrentTime = GetWorld()->GetRealTimeSeconds();

	if (bCanDash)
	{

		// If Player Double Taps the same direction
		if (CurrentTime - LastDashActionTappedTime < DoubleTapActivationDelay && Value.GetMagnitude() == PreviousDashDirection)
		{

			// Knock the actor up slightly to prevent ground collision
			LaunchCharacter(FVector(0, 0, 250), false, true); // Note: I like the feel of true Overrides but we can come back later.

			// Set Dash DirectionalValue to be used in DashDirectionLaunch
			DashDirectionalValue = Value.Get<FVector2D>();

			// After a tiny delay dash in desired direction
			GetWorld()->GetTimerManager().SetTimer(DashDirectionalMovementDelayTimerHandle, this, &APlayerCharacter::DashDirectionalLaunch, 0.065, false); // Note: This number will never change while running. 0.65 feels good.

			if(DashCameraShake)
				UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(DashCameraShake);

			bDashBlurFadingIn = true;
			GetWorld()->GetTimerManager().SetTimer(DashBlurTimerHandle, this, &APlayerCharacter::ClearDashBlur, DashBlurUpTime, false);

			if(SoundManagerSubSystem)
			{
				SoundManagerSubSystem->PlaySound(this->GetActorLocation(), DashSC);
			}
		}
	}

	LastDashActionTappedTime = CurrentTime;
	PreviousDashDirection = Value.GetMagnitude();
}

void APlayerCharacter::DashDirectionalLaunch()
{
	const float PreDashSpeed = GetVelocity().Length();

	if (DashDirectionalValue.Y == 1)
		LaunchCharacter(GetActorForwardVector() * DashDistance, true, false);
	else if (DashDirectionalValue.Y == -1)
		LaunchCharacter(-GetActorForwardVector() * DashDistance, true, false);
	else if (DashDirectionalValue.X == -1)
		LaunchCharacter(-GetActorRightVector() * DashDistance, true, false);
	else if (DashDirectionalValue.X == 1)
		LaunchCharacter(GetActorRightVector() * DashDistance, true, false);

	// Handle velocity after dash
	FVector PostDashDirection = UKismetMathLibrary::Conv_RotatorToVector(GetCharacterMovement()->GetLastUpdateRotation());
	PostDashDirection *= PreDashSpeed;
	GetCharacterMovement()->Velocity = PostDashDirection;

	// Handle Dash Cooldown
	bCanDash = false;
	GetWorld()->GetTimerManager().SetTimer(DashCooldownTimerHandle, this, &APlayerCharacter::ResetDashCooldown, DashCooldownTime, false);

	LastDashActionTappedTime = 0;
}

void APlayerCharacter::ClearDashBlur()
{
	bDashBlurFadingIn = false;
	Camera->PostProcessSettings.WeightedBlendables.Array[0].Weight = 0;
}

void APlayerCharacter::ResetDashCooldown()
{
	bCanDash = true;
}

void APlayerCharacter::Look(const FInputActionValue &Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this));
		AddControllerPitchInput(LookAxisValue.Y * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this));
	}
}

void APlayerCharacter::Sprint(const FInputActionValue &Value)
{
	bIsSprinting = Value.Get<bool>();
}

void APlayerCharacter::Crouch(const FInputActionValue &Value)
{
	if (Value.Get<bool>())
	{
		Super::Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void APlayerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (HalfHeightAdjust == 0.f)
	{
		return;
	}

	float StartBaseEyeHeight = BaseEyeHeight;
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CrouchEyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight + HalfHeightAdjust;
	Camera->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight), false);
}

void APlayerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	float StartBaseEyeHeight = BaseEyeHeight;
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CrouchEyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight - HalfHeightAdjust;
	Camera->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight), false);
}

void APlayerCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo &OutResult)
{
	if (Camera)
	{
		Camera->GetCameraView(DeltaTime, OutResult);
		OutResult.Location += CrouchEyeOffset;
	}
}

void APlayerCharacter::Attack(const FInputActionValue &Value)
{
	if(bCanAttack)
	{
		if(bIsSwappingWeapon)
			return;
	
		if (bIsSprinting)
			return;
		ActiveWeapon->Shoot();
	}
}

void APlayerCharacter::Grapple(const FInputActionValue &Value)
{
	if (!Value.Get<bool>())
	{
		GrappleComponent->CancelGrapple();
		return;
	}
	if (GrappleComponent->GrappleState != EGrappleState::ReadyToFire)
	{
		return;
	}
	FHitResult HitResult;
	FVector StartLocation = Camera->GetComponentLocation() + Camera->GetForwardVector() * GRAPPLE_TRACE_START_FORWARD_BUFFER;
	FVector EndLocation = Camera->GetForwardVector() * GrappleComponent->GrappleRange + StartLocation;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);
	// DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 5.f);
	FVector TargetLocation = EndLocation;
	if (AActor *HitActor = HitResult.GetActor())
	{
		TargetLocation = HitResult.ImpactPoint;
	}
	GrappleComponent->Fire(TargetLocation);

	// ToDo: Implement sound here (grapple shot)
}

void APlayerCharacter::SwitchWeapon(const FInputActionValue &Value)
{

	
	
	if(Weapon1 && Weapon2 && bIsSwappingWeapon != true)
	{
		if(ActiveWeapon->GunChangeAudioComp)
			ActiveWeapon->GunChangeAudioComp->Play();
		
		bIsSwappingWeapon = true;
		GetWorld()->GetTimerManager().SetTimer(IsSwappingTimerHandle, this, &APlayerCharacter::ToggleIsSwappingOff, .5f, false);
		ActiveWeapon = (ActiveWeapon == Weapon1) ? Weapon2 : Weapon1;
		StashedWeapon = (ActiveWeapon == Weapon1) ? Weapon2 : Weapon1;
		StashedWeapon->SetActorHiddenInGame(true);
		ActiveWeapon->SetActorHiddenInGame(false);
		PlayerHUDWidgetInstance->SetWeaponIcons(ActiveWeapon->GetWeaponIcon(), StashedWeapon->GetWeaponIcon());
	}
}

void APlayerCharacter::SetWeapon1(AWeaponBase *Weapon)
{
	Weapon1 = Weapon;
	ActiveWeapon = Weapon1;
}

void APlayerCharacter::SetWeapon2(AWeaponBase *Weapon)
{
	Weapon2 = Weapon;
	ActiveWeapon = Weapon2;
}

AWeaponBase *APlayerCharacter::GetWeapon1() const
{
	return Weapon1;
}

AWeaponBase *APlayerCharacter::GetWeapon2() const
{
	return Weapon2;
}

void APlayerCharacter::SetIsMantleing(bool IsMantleingStatus)
{
	bIsMantleing = IsMantleingStatus;
}

void APlayerCharacter::DamageActor(AActor* DamagingActor, const float DamageAmount, FName HitBoneName)
{

	IDamageableActor::DamageActor(DamagingActor, DamageAmount);
	
	if (HealthComponent)
	{
		if(DamageCameraShake)
			UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(DamageCameraShake);
		HealthComponent->SetHealth(HealthComponent->GetHealth() - DamageAmount);
		UpdateHealthBar();
	}

	// Set DirectionalDamageIndicator to rotate
	if(DirectionalDamageIndicatorWidget)
		DirectionalDamageIndicatorWidget->SetDamagingActor(DamagingActor);
	
	HealthComponent->SetHealth(HealthComponent->GetHealth() - DamageAmount);

	if(HealthComponent->GetHealth() <= 0)
		CurrentGameMode->EndRun();
		
}

void APlayerCharacter::ChangeCrosshair()
{
	if(OnDamagedDelegate.IsBound())
		OnDamagedDelegate.Execute();
}

void APlayerCharacter::Heal(int Value)
{
	if (!HealthComponent)
		return;
	HealthComponent->SetHealth(HealthComponent->GetHealth() + Value);
	UpdateHealthBar();
}

void APlayerCharacter::HealByPercentage(int Percentage)
{
	if (!HealthComponent)
		return;
	HealthComponent->SetHealth(HealthComponent->GetHealth() + HealthComponent->GetMaxHealth() * Percentage / 100);
	UpdateHealthBar();
}

float APlayerCharacter::GetMaxHealth() const
{
	return HealthComponent->GetMaxHealth();
}

UGrappleComponent *APlayerCharacter::GetGrappleComponent()
{
	return GrappleComponent;
}

void APlayerCharacter::UpdateHealthBar()
{
	if (OnHealthChangedDelegate.IsBound())
	{
		OnHealthChangedDelegate.Execute(HealthComponent->GetHealth());
	}
}

// Temporary
void APlayerCharacter::DEBUG_SpawnWave()
{
	if(CurrentGameMode)
		CurrentGameMode->SpawnWave();
}

UUpgradeSystemComponent* APlayerCharacter::GetUpgradeSystemComponent()
{
	if(UpgradeSystemComponent)
		return UpgradeSystemComponent;
	else
		return nullptr;
}

void APlayerCharacter::CheckGround()
{
	
			FHitResult HitResult;

			FVector StartTrace = this->GetActorLocation();
			StartTrace.Z -= 10; // TEMP: Offset to make debug draw lines visible without moving.
			FVector DownVector = this->GetActorUpVector();
			FVector EndTrace = ((DownVector * 100.f * -1) + StartTrace);
			FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
			TraceParams->bReturnPhysicalMaterial = true;  // Hit must return a physical material to tell if the player has hit a headshot.
			TraceParams->AddIgnoredComponent(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh());
			
			
			if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
			{
				// Get Surface Type to check for headshot and impact material type.
				EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
					if(CurrentGroundMat != Cast<UPhysicalMaterial>(HitResult.PhysMaterial.Get()))
					{
						CurrentGroundMat = Cast<UPhysicalMaterial>(HitResult.PhysMaterial.Get());
						switch (HitSurfaceType)
						{
						case SURFACE_Rock:
							if(RockStepSound)
							{
								FootStepAudioComp->SetSound(RockStepSound);
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Rock");
							}
							if(RockLandSound)
							{
								LandingAudioComp->SetSound(RockLandSound);
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"LandSound is now Rock");
							}
							break;
						case SURFACE_Wood:
							if(WoodStepSound)
							{
								FootStepAudioComp->SetSound(WoodStepSound);
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Wood");
							}
							if(WoodLandSound)
							{
								LandingAudioComp->SetSound(WoodLandSound);
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"LandSound is now Wood");
							}
							break;
						case SURFACE_Grass:
							if(GrassStepSound)
							{
								FootStepAudioComp->SetSound(GrassStepSound);
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Grass");
							}
							if(GrassLandSound)
							{
								LandingAudioComp->SetSound(GrassLandSound);
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"LandSound is now Grass");
							}
							break;
						case SURFACE_Water:
							if(WaterStepSound)
							{
								FootStepAudioComp->SetSound(WaterStepSound);
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Water");
							}
							if(WaterLandSound)
							{
								LandingAudioComp->SetSound(WaterLandSound);
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"LandSound is now Water");
							}
							break;
						default:
							if(RockStepSound)
							{
								FootStepAudioComp->SetSound(RockStepSound);
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"StepSound is now Rock");
							}
							if(RockLandSound)
							{
								LandingAudioComp->SetSound(RockLandSound);
								GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,"LandSound is now Rock");
							}
							break;
						}
					}
			}
}
