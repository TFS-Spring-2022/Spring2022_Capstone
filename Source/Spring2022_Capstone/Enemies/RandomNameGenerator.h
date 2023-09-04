// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RandomNameGenerator.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SPRING2022_CAPSTONE_API URandomNameGenerator : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Names")
	TArray<FText> FirstNames;

	UPROPERTY(EditAnywhere, Category = "Names")
	TArray<FText> LastNames;

	UPROPERTY(EditAnywhere, Category = "Names")
	TArray<FText> FullNames;

public:

	FText GetRandomFirstName();

	FText GetRandomLastName();

	FText GetRandomFullName();
	
};
