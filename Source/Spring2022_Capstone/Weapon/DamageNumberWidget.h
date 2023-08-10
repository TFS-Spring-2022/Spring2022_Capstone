// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageNumberWidget.generated.h"

/**
 * Widget class for displaying damage numbers.
 */
UCLASS()
class SPRING2022_CAPSTONE_API UDamageNumberWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetDamageText(const FText& Text);

	UFUNCTION(BlueprintCallable)
	void SetColorBySurfaceType(EPhysicalSurface SurfaceType);

	UFUNCTION()
	void Despawn();

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DamageTextBlock;

public:
	FTimerHandle DespawnTimerHandle;
};