// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "NotificationWidget.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "NotificationUIManager.generated.h"

UCLASS()
class SPRING2022_CAPSTONE_API ANotificationUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANotificationUIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Components", meta=(AllowPrivateAccess = true))
	USphereComponent* NotificationZoneCollider;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	// NotificationWidget BP to be created.
	UPROPERTY(EditAnywhere, Category = "Notification Manager")
	TSubclassOf<UNotificationWidget> NotificationWidget;

	// Notification instance.
	UPROPERTY()
	UNotificationWidget* _NotificationWidget;

	// If true: NotificationWidget Instance's Notification text will be overwritten with NewNotificationText.
	UPROPERTY(EditAnywhere, Category = "Notification Manager")
	bool bOverwriteNotificationText = false;
	
	// Text that will overwrite notification bp if OverwriteNotificationText == true.
	UPROPERTY(EditAnywhere, Category = "Notification Manager")
	FText NewNotificationText;
	
	// Time the notification will be shown for.
	UPROPERTY(EditAnywhere, Category = "Notification Manager")
	float SecondsDisplayed;

	// Timer to handle notification display time.
	FTimerHandle NotificationDisplayTimerHandle;	
	
	/**
	 * @brief Called automatically after SecondsDisplayed has elapsed.
	 * Removes the NotificationWidget or Destroys based on bDestroyAfterViewing.
	 */
	UFUNCTION()
	void DismissNotification();

	UPROPERTY(EditAnywhere, Category = "Notification Manager")
	bool bDestroyAfterViewing;
	
	bool bNotificationIsShowing;

};
