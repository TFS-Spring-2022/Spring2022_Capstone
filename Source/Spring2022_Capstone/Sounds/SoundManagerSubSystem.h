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
	
	USoundManagerSubSystem();

	int SoundEventToken = 0;
	int GruntSoundEventToken = 0;
	int SniperSoundEventToken = 0;
	int NarratorSoundEventToken = 0;
	int PlayerSoundEventToken = 0;

public:
	
	UFUNCTION()
	void PlaySound(const FVector& Location, USoundBase* Sound) const;

	UFUNCTION()
	void PlaysMusic(const USoundCue* Music) const;

	UFUNCTION()
	void ResetEventTokens();

	UFUNCTION()
	void PlaySniperSoundEvent(UAudioComponent* OwnerAC, int eventID);

	UFUNCTION()
	void PlayGruntSoundEvent(UAudioComponent* OwnerAC, int eventID);

	UFUNCTION()
	void PlayNarratorSoundEvent(UAudioComponent* OwnerAC, int eventID);
	
	UFUNCTION()
	void PlayPlayerSoundEvent(UAudioComponent* OwnerAC, int eventID);

	UFUNCTION()
	void ToggleMusicOff(UAudioComponent* MusicAudioComp);

	UFUNCTION()
	void ToggleMusicOn(UAudioComponent* MusicAudioComp);

	UFUNCTION()
	void WaveStart(AActor* Actor);


	
	
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

	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerOverHeatSC;
	
	UPROPERTY(EditAnywhere, Category = "Player Voice Lines")
	USoundCue* PlayerMissSC;

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
	USoundCue* RangerDeathSC;

	UPROPERTY(EditAnywhere, Category = "Ranger Voice Lines")
	USoundCue* RangerDisabledSC;

	UPROPERTY(EditAnywhere, Category = "Ranger Voice Lines")
	USoundCue* RangerFearSC;
	
#pragma endregion
#pragma region Grunt Voices
	
	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntHurtSC;

	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntJumpSC;

	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntWaveStartSC;

	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntBarrelSC;

	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntGrappleSC;

	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntDeathSC;
	
	UPROPERTY(EditAnywhere, Category = "Grunt Voice Lines")
	USoundCue* GruntArialHitSC;
	
#pragma endregion 

#pragma 
	
	UPROPERTY(EditAnywhere, Category = "Wave Sound")
	USoundCue* WaveStartSound;
	
	UPROPERTY(EditAnywhere, Category = "Menu Music")
	USoundCue* MainMenuMusic;

	UPROPERTY(EditAnywhere, Category = "Menu sounds")
	USoundCue* HoverButtonSound;

	UPROPERTY(EditAnywhere, Category = "Menu sounds")
	USoundCue* ClickButtonSound;

	UPROPERTY(EditAnywhere, Category = "Audio C")
	UAudioComponent* SubSystemAudio;
};
