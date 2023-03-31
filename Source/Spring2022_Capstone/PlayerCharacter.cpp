// Created by Spring2022_Capstone team

#include "PlayerCharacter.h"

#include <string>

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Weapon/WeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	Camera->bUsePawnControlRotation = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	CrouchEyeOffset = FVector(0.f);
	CrouchSpeed = 12.f;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Crouch);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
		EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Completed, this,
										   &APlayerCharacter::SwitchWeapon);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Sprint);
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

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
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float CrouchInterpTime = FMath::Min(1.f, CrouchSpeed * DeltaTime);
	CrouchEyeOffset = (1.f - CrouchInterpTime) * CrouchEyeOffset;
}

void APlayerCharacter::Move(const FInputActionValue &Value)
{
	const FVector2D DirectionalValue = Value.Get<FVector2D>();
	if (GetController() && (DirectionalValue.X != 0.f || DirectionalValue.Y != 0.f))
	{
		GetCharacterMovement()->MaxWalkSpeed = bIsSprinting ? Speed * SprintMultiplier : Speed;
		AddMovementInput(GetActorForwardVector(), DirectionalValue.Y * 100);
		AddMovementInput(GetActorRightVector(), DirectionalValue.X * 100);
	}
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
	ActiveWeapon->Shoot();
}

void APlayerCharacter::SwitchWeapon(const FInputActionValue &Value)
{
	ActiveWeapon = (ActiveWeapon == Weapon1) ? Weapon2 : Weapon1;
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

void APlayerCharacter::TakeHit()
{
	if (HealthComponent)
	{
		HealthComponent->SetHealth(HealthComponent->GetHealth() - 5.0f);
		UpdateHealthBar();
	}
}

void APlayerCharacter::HealByPercentage(int percentage)
{
	if (HealthComponent)
	{
	HealthComponent->SetHealth(HealthComponent->GetHealth() + HealthComponent->GetMaxHealth() * percentage / 100);
	UpdateHealthBar();
	}
}

float APlayerCharacter::GetMaxHealth()
{
    return HealthComponent->GetMaxHealth();
}

void APlayerCharacter::UpdateHealthBar()
{
	if (OnHealthChangedDelegate.IsBound())
	{
		OnHealthChangedDelegate.Execute(HealthComponent->GetHealth());
	}
}
