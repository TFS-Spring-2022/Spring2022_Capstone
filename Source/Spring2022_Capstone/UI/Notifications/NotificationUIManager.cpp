// Created by Spring2022_Capstone team


#include "NotificationUIManager.h"

// Sets default values
ANotificationUIManager::ANotificationUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // can probably be false

	NotificationZoneCollider = CreateDefaultSubobject<USphereComponent>("Notification Zone Collider");
	RootComponent = NotificationZoneCollider;

}

// Called when the game starts or when spawned
void ANotificationUIManager::BeginPlay()
{
	Super::BeginPlay();

	NotificationZoneCollider->OnComponentBeginOverlap.AddDynamic(this, &ANotificationUIManager::OnOverlapBegin);

	bNotificationIsShowing = false;
	
}

// Called every frame
void ANotificationUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ANotificationUIManager::OnOverlapBegin(UPrimitiveComponent* Comp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if(!bNotificationIsShowing && NotificationWidget)
	{
		
		// Display Notification
		_NotificationWidget = Cast<UNotificationWidget>(CreateWidget(GetWorld(), NotificationWidget));

		// Overwrite Notification's text instance with NewNotificationText set in details.
		if(bOverwriteNotificationText)
			_NotificationWidget->ChangeNotificationText(NewNotificationText);
		
		_NotificationWidget->AddToViewport(1);

		bNotificationIsShowing = true;
		
		GetWorldTimerManager().SetTimer(NotificationDisplayTimerHandle, this, &ANotificationUIManager::DismissNotification, SecondsDisplayed, false);
	}
	
}

void ANotificationUIManager::DismissNotification()
{

	if(bDestroyAfterViewing)
		Destroy();
	
	if(_NotificationWidget)
		_NotificationWidget->RemoveFromParent();
	
	bNotificationIsShowing = false;
}

