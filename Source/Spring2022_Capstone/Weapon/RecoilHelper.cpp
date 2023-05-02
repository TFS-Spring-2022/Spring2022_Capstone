// Created by Spring2022_Capstone team


#include "RecoilHelper.h"

// Sets default values for this component's properties
URecoilHelper::URecoilHelper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void URecoilHelper::BeginPlay()
{
	Super::BeginPlay();

	OwningParentWeapon = Cast<AWeaponBase>(GetOwner()); // Question: Will this cause an issue from the child shotgun/semi classes? I do not believe so test later.
	
	OwnersPlayerController = GetWorld()->GetFirstPlayerController(); 
	
}


// Called every frame
void URecoilHelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

