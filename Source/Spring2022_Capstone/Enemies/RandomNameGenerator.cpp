// Created by Spring2022_Capstone team


#include "RandomNameGenerator.h"

#include "Kismet/KismetMathLibrary.h"

FText URandomNameGenerator::GetRandomFirstName()
{
	// If no first names return a default first name.
	if(FirstNames.IsEmpty())
		return FText::FromString("JohnJane");

	return FirstNames[UKismetMathLibrary::RandomIntegerInRange(0, FirstNames.Num() - 1)];
}

FText URandomNameGenerator::GetRandomLastName()
{
	// If no last names return a default last name.
	if(LastNames.IsEmpty())
		return FText::FromString("Doe");

	return LastNames[UKismetMathLibrary::RandomIntegerInRange(0, LastNames.Num() - 1)];
	
}

FText URandomNameGenerator::GetRandomFullName()
{
	// If no full names return a default full name.
	if(FullNames.IsEmpty())
		return FText::FromString("JohnJane Doe");

	return FullNames[UKismetMathLibrary::RandomIntegerInRange(0, FullNames.Num() - 1)];
}
