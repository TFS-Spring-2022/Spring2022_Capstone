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
#include "Spring2022_Capstone/CustomGameUserSettings.h"

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
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Pause);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Dash);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(GrappleAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Grapple);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::CCrouch);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
		EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Completed, this,
										   &APlayerCharacter::PlaySwitchWeaponAnimation);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Sprint);
		EnhancedInputComponent->BindAction(InspectWeaponAction, ETriggerEvent::Triggered, this, &APlayerCharacter::InspectWeapon);
		EnhancedInputComponent->BindAction(InspectGrappleAction, ETriggerEvent::Triggered, this, &APlayerCharacter::InspectGrapple);
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	const UGameInstance *GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	SoundManagerSubSystem = GameInstance->GetSubsystem<USoundManagerSubSystem>();

	FootStepAudioComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	LandingAudioComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CheckGround();

	// Temp
	SoundManagerSubSystem->PlaySoundEvent();

	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
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
	if (PlayerHUDWidgetBP)
	{
		PlayerHUDWidgetInstance = Cast<UHUDWidget>(CreateWidget(GetWorld(), PlayerHUDWidgetBP));
		PlayerHUDWidgetInstance->AddToViewport(1);
	}
	// Create and add Damage Indicator Widget
	if (DamageIndicatorWidgetBP)
	{
		DirectionalDamageIndicatorWidget = Cast<UDirectionalDamageIndicatorWidget>(CreateWidget(GetWorld(), DamageIndicatorWidgetBP));
		DirectionalDamageIndicatorWidget->AddToViewport(1);
	}
	// Create and add Pause Menu Widget
	if (PauseMenuWidgetBP)
	{
		PauseMenuWidgetInstance = Cast<UPauseMenuWidget>(CreateWidget(GetWorld(), PauseMenuWidgetBP));
		PauseMenuWidgetInstance->AddToViewport(1);
		PauseMenuWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	}

	bDashBlurFadingIn = false;
	CurrentGameMode = Cast<ASpring2022_CapstoneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	ScoreManagerSubsystem = GetGameInstance()->GetSubsystem<UScoreSystemManagerSubSystem>();
	if (ScoreManagerSubsystem)
		ScoreManagerSubsystem->SetPlayerReference(this);
	ScoreManagerTimerSubSystem = GetWorld()->GetSubsystem<UScoreSystemTimerSubSystem>();
	if (ScoreManagerTimerSubSystem)
	{
		ScoreManagerTimerSubSystem->SetPlayerReference(this);
		ScoreManagerTimerSubSystem->SetScoreManagerSubSystem(ScoreManagerSubsystem);
	}

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController(), false);

	bHasSniperDisableObject = false;
	bIsSwappingWeapon = false;
	bCanAttack = true;

	// Load Settings
	YSensitivity = UCustomGameUserSettings::GetCustomGameUserSettings()->YSensitivity;
	XSensitivity = UCustomGameUserSettings::GetCustomGameUserSettings()->XSensitivity;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float CrouchInterpTime = FMath::Min(1.f, CrouchSpeed * DeltaTime);
	CrouchEyeOffset = (1.f - CrouchInterpTime) * CrouchEyeOffset;
	CheckGround();

	if (ScoreManagerTimerSubSystem)
	{
		if (GetMovementComponent()->IsFalling())
		{
			ScoreManagerTimerSubSystem->StopAccoladeTimer(EAccolades::LandLubber);

			if (ScoreManagerTimerSubSystem->IsAccoladeTimerRunning(EAccolades::SkyPirate) == false)
				ScoreManagerTimerSubSystem->StartAccoladeTimer(EAccolades::SkyPirate);
		}
		if (GetMovementComponent()->IsMovingOnGround())
		{
			ScoreManagerTimerSubSystem->StopAccoladeTimer(EAccolades::SkyPirate);

			if (ScoreManagerTimerSubSystem->IsAccoladeTimerRunning(EAccolades::LandLubber) == false)
				ScoreManagerTimerSubSystem->StartAccoladeTimer(EAccolades::LandLubber);
		}
	}

	if (bDashBlurFadingIn)
		Camera->PostProcessSettings.WeightedBlendables.Array[0].Weight = FMath::FInterpTo(Camera->PostProcessSettings.WeightedBlendables.Array[0].Weight, 1, DeltaTime, DASH_BLUR_FADEIN_SPEED);

	ActiveWeapon->SetActorHiddenInGame(false);
}

void APlayerCharacter::Pause(const FInputActionValue &Value)
{
	if (!PauseMenuWidgetInstance)
		return;

	if (!UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, PauseMenuWidgetInstance);
		PlayerController->SetIgnoreLookInput(true);
		PlayerController->SetIgnoreMoveInput(true);
		SetCanAttack(false);
		PlayerController->bShowMouseCursor = true;
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		PauseMenuWidgetInstance->SetVisibility(ESlateVisibility::Visible);
	}
	else
		UnPause();
}

void APlayerCharacter::UnPause()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		PlayerController->SetIgnoreLookInput(false);
		PlayerController->SetIgnoreMoveInput(false);
		SetCanAttack(true);
		PlayerController->bShowMouseCursor = false;
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController, false);
		PauseMenuWidgetInstance->HideSettingsMenu();
		PauseMenuWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerCharacter::PlayOverheatMontage(bool bFinishOverheatAnimation)
{
	if (!OverheatMontage)
		return;

	if (!bFinishOverheatAnimation)
	{
		// Note - Setting bEnableAutoBlendOut to false is not causing the gun to hold at final frame. ToDo: Figure out how to loop end.
		OverheatMontage->bEnableAutoBlendOut = false;
		PlayAnimMontage(OverheatMontage, 1.0, "OverheatStart");
	}
	else
	{
		OverheatMontage->bEnableAutoBlendOut = true;
		PlayAnimMontage(OverheatMontage, 1.0, "OverheatEnd");
	}
}

void APlayerCharacter::Move(const FInputActionValue &Value)
{
	DirectionalMovementValue = Value.Get<FVector2D>();

	// Disable vertical movement when grappling to prevent weird throws from happening (could also divide by liek .8 or something test).
	if (GrappleComponent->GrappleState == EGrappleState::Attached)
	{
		// Stop vertical input
		DirectionalMovementValue.Y = 0;
	}

	if (GetController() && (DirectionalMovementValue.X != 0.f || DirectionalMovementValue.Y != 0.f))
	{
		bIsMoving = true;
		if (isGrounded)
		{
			if (FootStepAudioComp->GetSound())
				if (!FootStepAudioComp->IsPlaying())
					FootStepAudioComp->Play();
		}
		GetCharacterMovement()->MaxWalkSpeed = bIsSprinting ? Speed * SprintMultiplier : Speed;
		AddMovementInput(GetActorForwardVector(), DirectionalMovementValue.Y * 100);
		AddMovementInput(GetActorRightVector(), DirectionalMovementValue.X * 100);
	}
	else
	{
		bIsMoving = false;
		FootStepAudioComp->Stop();
	}
}

void APlayerCharacter::Jump()
{
	if (!bIsMantleing)
	{
		if (bIsMoving)
		{
			if (PlayerMantleSystemComponent->AttemptMantle())
			{
				if (SoundManagerSubSystem)
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

void APlayerCharacter::Landed(const FHitResult &Hit)
{
	Super::Landed(Hit);

	if (ScoreManagerTimerSubSystem)
		ScoreManagerTimerSubSystem->StopAccoladeTimer(EAccolades::SkyPirate);
}

void APlayerCharacter::Dash(const FInputActionValue &Value)
{
	const float CurrentTime = GetWorld()->GetRealTimeSeconds();

	if (GetController() && (DirectionalMovementValue.X != 0.f || DirectionalMovementValue.Y != 0.f))
		if (bCanDash)
		{
			// Knock the actor up slightly to prevent ground collision
			LaunchCharacter(FVector(0, 0, 250), false, true); // Note: I like the feel of true Overrides but we can come back later.

			// Set Dash DirectionalValue to be used in DashDirectionLaunch
			DashDirectionalValue = DirectionalMovementValue;

			// After a tiny delay dash in desired direction
			GetWorld()->GetTimerManager().SetTimer(DashDirectionalMovementDelayTimerHandle, this, &APlayerCharacter::DashDirectionalLaunch, 0.065, false); // Note: This number will never change while running. 0.65 feels good.

			if (DashCameraShake)
				UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(DashCameraShake);

			bDashBlurFadingIn = true;
			GetWorld()->GetTimerManager().SetTimer(DashBlurTimerHandle, this, &APlayerCharacter::ClearDashBlur, DashBlurUpTime, false);

			if (SoundManagerSubSystem)
				SoundManagerSubSystem->PlaySound(this->GetActorLocation(), DashSC);
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
		AddControllerYawInput(LookAxisValue.X * YSensitivity * UGameplayStatics::GetWorldDeltaSeconds(this));
		AddControllerPitchInput(LookAxisValue.Y * XSensitivity * UGameplayStatics::GetWorldDeltaSeconds(this));
	}
}

void APlayerCharacter::Sprint(const FInputActionValue &Value)
{
	if (Value.Get<bool>())
	{
		FootStepAudioComp->SetPitchMultiplier(2.f);
	}
	else
	{
		FootStepAudioComp->SetPitchMultiplier(1.4f);
	}
	bIsSprinting = Value.Get<bool>();
}

void APlayerCharacter::CCrouch(const FInputActionValue &Value)
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

	if (bIsSwappingWeapon)
		return;

	if (bCanAttack)
	{
		if (bIsSprinting)
			return;
		if (ActiveWeapon->Shoot())
		{
			if (FireMontage)
				PlayAnimMontage(FireMontage, 1.0, "HeavyShot");
		}

		GetWorld()->GetTimerManager().SetTimer(BetweenShotTimerHandle, this, &APlayerCharacter::SetCanAttackTrue, ActiveWeapon->GetFireRate(), false);
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
	FVector GrappleTargetLocation = EndLocation;
	if (AActor *HitActor = HitResult.GetActor())
	{
		GrappleTargetLocation = HitResult.ImpactPoint;
	}

	if (GrappleLaunchMontage)
		PlayAnimMontage(GrappleLaunchMontage, 1.0, "GrappleLaunch");

	// ToDo: Attach grapple to edge of stump. Then calling after a delay will look nicer.
	// GetWorld()->GetTimerManager().SetTimer(DelayGrappleTimerHandle, this, &APlayerCharacter::FireGrappleAfterDelay, 1, false);
	GrappleComponent->Fire(GrappleTargetLocation);

	// ToDo: Implement sound here (grapple shot)
}

void APlayerCharacter::FireGrappleAfterDelay()
{
	// ToDo: Very short delay so grapple stump can enter screen before firing.
}

void APlayerCharacter::InspectWeapon(const FInputActionValue &Value)
{
	if (InspectWeaponMontage)
		PlayAnimMontage(InspectWeaponMontage);
}

void APlayerCharacter::InspectGrapple(const FInputActionValue &Value)
{
	if (InspectGrappleMontage)
		PlayAnimMontage(InspectGrappleMontage);
}

void APlayerCharacter::SwitchWeapon()
{
	if (Weapon1 && Weapon2)
	{
		if (ActiveWeapon->GunChangeAudioComp)
			ActiveWeapon->GunChangeAudioComp->Play();

		GetWorld()->GetTimerManager().SetTimer(IsSwappingTimerHandle, this, &APlayerCharacter::ToggleIsSwappingOff, .2f, false); // Backup incase problem with swap animation not finishing.
		ActiveWeapon = (ActiveWeapon == Weapon1) ? Weapon2 : Weapon1;
		StashedWeapon = (ActiveWeapon == Weapon1) ? Weapon2 : Weapon1;
		StashedWeapon->SetActorHiddenInGame(true);
		ActiveWeapon->SetActorHiddenInGame(false);
		PlayerHUDWidgetInstance->SetWeaponIcons(ActiveWeapon->GetWeaponIcon(), StashedWeapon->GetWeaponIcon());
	}
}

void APlayerCharacter::PlaySwitchWeaponAnimation(const FInputActionValue &Value)
{
	if (Weapon1 && Weapon2 && bIsSwappingWeapon != true)
		bIsSwappingWeapon = true;
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

bool APlayerCharacter::DamageActor(AActor *DamagingActor, const float DamageAmount, FName HitBoneName)
{

	IDamageableActor::DamageActor(DamagingActor, DamageAmount);

	if (!HealthComponent) { return false; }

	if (ScoreManagerTimerSubSystem && ScoreManagerTimerSubSystem->IsAccoladeTimerRunning(CloseCallCorsair) == false) 
		ScoreManagerTimerSubSystem->StartAccoladeTimer(EAccolades::CloseCallCorsair);

	if (DamageCameraShake)
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(DamageCameraShake);
		
	// Set DirectionalDamageIndicator to rotate
	if (DirectionalDamageIndicatorWidget)
		DirectionalDamageIndicatorWidget->SetDamagingActor(DamagingActor);

	HealthComponent->SetHealth(HealthComponent->GetHealth() - DamageAmount);
	UpdateHealthBar();
	if (HealthComponent->GetHealth() <= 0)
	{
		CurrentGameMode->EndRun();
		return true;
	}
	return false;
}

void APlayerCharacter::ChangeCrosshair()
{
	if (OnDamagedDelegate.IsBound())
		OnDamagedDelegate.Execute();
}

void APlayerCharacter::Heal(int Value)
{

	bool bIsBelowDeathDodgerPercentage = false;

	if (!HealthComponent)
		return;

	if (GetCurrentHealth() < ScoreManagerSubsystem->GetDeathDodgerHealthPercentage() / 100 * GetMaxHealth())
		bIsBelowDeathDodgerPercentage = true;

	HealthComponent->SetHealth(HealthComponent->GetHealth() + Value);
	UpdateHealthBar();

	if (GetCurrentHealth() > ScoreManagerSubsystem->GetDeathDodgerHealthPercentage() / 100 * GetMaxHealth() && bIsBelowDeathDodgerPercentage)
		ScoreManagerSubsystem->IncrementDeathDodgerCount();
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

float APlayerCharacter::GetCurrentHealth() const
{
	return HealthComponent->GetHealth();
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
	if (CurrentGameMode)
		CurrentGameMode->SpawnWave();
}

UUpgradeSystemComponent *APlayerCharacter::GetUpgradeSystemComponent()
{
	if (UpgradeSystemComponent)
		return UpgradeSystemComponent;
	else
		return nullptr;
}

void APlayerCharacter::CheckGround()
{

	FHitResult HitResult;

	FVector StartTrace = this->GetActorLocation();
	FVector DownVector = FVector(0, 0, 1);
	FVector EndTrace = ((DownVector * 120.f * -1) + StartTrace);
	FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
	TraceParams->bReturnPhysicalMaterial = true;
	TraceParams->AddIgnoredComponent(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh());

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
		if (!isGrounded)
		{
			LandingAudioComp->Play();
			isGrounded = true;
		}
		EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
		if (CurrentGroundMat != Cast<UPhysicalMaterial>(HitResult.PhysMaterial.Get()))
		{
			CurrentGroundMat = Cast<UPhysicalMaterial>(HitResult.PhysMaterial.Get());
			switch (HitSurfaceType)
			{
			case SURFACE_Rock:
				if (RockStepSound)
					FootStepAudioComp->SetSound(RockStepSound);
				if (RockLandSound)
					LandingAudioComp->SetSound(RockLandSound);
				break;
			case SURFACE_Wood:
				if (WoodStepSound)
					FootStepAudioComp->SetSound(WoodStepSound);
				if (WoodLandSound)
					LandingAudioComp->SetSound(WoodLandSound);
				break;
			case SURFACE_Grass:
				FootStepAudioComp->SetSound(GrassStepSound);
				if (GrassLandSound)
					LandingAudioComp->SetSound(GrassLandSound);
				break;
			case SURFACE_Water:
				if (WaterStepSound)
					FootStepAudioComp->SetSound(WaterStepSound);
				if (WaterLandSound)
					LandingAudioComp->SetSound(WaterLandSound);
				break;
			default:
				if (RockStepSound)
					FootStepAudioComp->SetSound(RockStepSound);
				if (RockLandSound)
					LandingAudioComp->SetSound(RockLandSound);
				break;
			}
		}
	}
	else
	{
		if (isGrounded)
		{
			isGrounded = false;
			FootStepAudioComp->Stop();
		}
	}
}

void APlayerCharacter::SetYSensitivity(float Value) 
{
	YSensitivity = Value;
}

void APlayerCharacter::SetXSensitivity(float Value) 
{
	XSensitivity = Value;
}
