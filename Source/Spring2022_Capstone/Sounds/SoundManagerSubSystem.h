// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SoundManagerSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class SPRING2022_CAPSTONE_API USoundManagerSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	

public:
	USoundManagerSubSystem();
	
	UFUNCTION()
	void PlaySound(const FVector& Location, USoundBase* Sound) const;

	UFUNCTION()
	void PlaysMusic(const USoundCue* Music) const;
	
	UFUNCTION()
	void PlaySoundEvent()const;

	UFUNCTION()
	void ImplementToken(int stk1, int ptk2, int gtk3, int sntk, int ntk);

	
private:

	UPROPERTY()
	TArray<USoundCue*> GruntVoiceLines;
	
	UPROPERTY()
	TArray<USoundCue*> PlayerVoiceLines;

	UPROPERTY()
	TArray<USoundCue*> SniperVoiceLines;

	UPROPERTY()
	TArray<USoundCue*> NarratorVoiceLines;

#pragma region Player Voices
	
	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerDeathSC;

	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerHurtSC;
	
	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerRampageSC;

	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerCritSC;

	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerHealedSC;

	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerHeavyHurtSC;

	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerWaveStartSC;

	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerSniperHitSC;

	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerAFKSC;

	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerGrapplingSC;

	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerArialSC;

#pragma endregion

#pragma region Narrator Voices
	
	UPROPERTY(EditAnywhere, Category = "Narrator Voice Lines")
	USoundCue* NarratorWaveStartSC;

	UPROPERTY(EditAnywhere, Category = "Narrator Voice Lines")
	USoundCue* NarratorHeavyHitSC;

	UPROPERTY(EditAnywhere, Category = "Narrator Voice Lines")
	USoundCue* NarratorRampageSC;

	UPROPERTY(EditAnywhere, Category = "Narrator Voice Lines")
	USoundCue* NarratorUpgradeOpenSC;

	UPROPERTY(EditAnywhere, Category = "Narrator Voice Lines")
	USoundCue* NarratorUpgradeSelectSC;

	UPROPERTY(EditAnywhere, Category = "Narrator Voice Lines")
	USoundCue* NarratorUpgradeDoubleJumpSC;

	UPROPERTY(EditAnywhere, Category = "Narrator Voice Lines")
	USoundCue* NarratorMaxGrappleSC;

	UPROPERTY(EditAnywhere, Category = "Narrator Voice Lines")
	USoundCue* NarratorRandomSC;

	UPROPERTY(EditAnywhere, Category = "Narrator Voice Lines")
	USoundCue* NarratorAFKUpgradeSC;

	UPROPERTY(EditAnywhere, Category = "Narrator Voice Lines")
	USoundCue* NarratorMaxSpeedSC;

	
#pragma endregion

#pragma region Ranger Voices

	UPROPERTY(EditAnywhere, Category = "Ranger Voice Lines")
	USoundCue* RangerLockOnSC;

	UPROPERTY(EditAnywhere, Category = "Ranger Voice Lines")
	USoundCue* RangerHurtSC;

	UPROPERTY(EditAnywhere, Category = "Ranger Voice Lines")
	USoundCue* RangerJumpSC;

	UPROPERTY(EditAnywhere, Category = "Ranger Voice Lines")
	USoundCue* RangerKillsPlayerSC;

	UPROPERTY(EditAnywhere, Category = "Ranger Voice Lines")
	USoundCue* RangerRandomSC;

	UPROPERTY(EditAnywhere, Category = "Ranger Voice Lines")
	USoundCue* RangerAirHitSC;

	UPROPERTY(EditAnywhere, Category = "Ranger Voice Lines")
	USoundCue* RangerDeath;
	
#pragma endregion

#pragma region Grunt Voices
	
	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntHurtSound;

	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntJumpSound;

	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntWaveStart;

	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntBarrelSC;

	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntGrappleSC;

	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntNumbersSC;
	
	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntArialHitSC;
	
#pragma endregion 

#pragma 
	
	UPROPERTY()
	int SoundEventToken;

	UPROPERTY()
	int GruntSoundEventToken;

	UPROPERTY()
	int SniperSoundEventToken;

	UPROPERTY()
	int NarratorSoundEventToken;

	UPROPERTY()
	int PlayerSoundEventToken;
	

	
	
	
	

	UPROPERTY(EditAnywhere, Category = "Menu Music")
	USoundCue* MainMenuMusic;

	UPROPERTY(EditAnywhere, Category = "Menu sounds")
	USoundCue* HoverButtonSound;

	UPROPERTY(EditAnywhere, Category = "Menu sounds")
	USoundCue* ClickButtonSound;

	UPROPERTY(EditAnywhere, Category = "Audio C")
	UAudioComponent* SubSystemAudio;
};
