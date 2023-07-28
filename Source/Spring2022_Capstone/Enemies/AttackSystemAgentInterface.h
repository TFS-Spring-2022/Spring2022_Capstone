// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackSystemAgentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttackSystemAgentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPRING2022_CAPSTONE_API IAttackSystemAgentInterface
{
	GENERATED_BODY()

public:

	// ToDo: virtual and in-line implementation if possible, ReleaseToken() might be possible.
	
	/**
	 * @brief Called from AIAttackSystemComponent when the system is giving an implementing Agent an attack token.
	 * @return True - Enemy received and holds token. False - Enemy could not receive token.
	 */
	bool ReceiveToken();

	/**
	 * @brief Called when an implementing Agent holding an attack token uses it, returning the logical token to the AIAttackSystemComponent. 
	 */
	void ReleaseToken();
	
};
