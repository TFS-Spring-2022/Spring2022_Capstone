// Created by Spring2022_Capstone team

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScoreSystemManager.generated.h"

/**
 * A class used to handle the score and accolades earned by a player through a run.
 */
UCLASS()
class SPRING2022_CAPSTONE_API UScoreSystemManager : public UObject
{
	GENERATED_BODY()

	// ToDo:
	// Accolades:
	// Brain Surgeon: 3 Headshots in 5 seconds.
	// Lord of War: 5 Kills in 5 seconds.
	// Sky Pirate: 15 seconds since last touched the ground.
	// Land Lubber: 30 seconds spent consecutively on the ground.
	// Bullet Sponge: Love over 60% max health in 3 seconds.
	// Opportunist: 4 enemies damaged by a single exploding hazard.
	// Giant Slayer: Elite killed in under 6 seconds (after first hit).
	// Last Shadow: 2 enemies killed while airborne.
	// Blunder Blast: More then 1 enemy killed with a shotgun blast on the ground.
	// Thunderclap: More then 1 enemy killed with a shotgun blast while airborne.
	// Cool Header: 1 minute spent between overheats.
	// Nimble Bones: 3 Sniper Shots avoided (zero damage).
	// Death Dodger: Recovered from less then 20% health 2 times in one wave.
	// No Sweat: Spent more then half the wave duration at over 50% health.
	// 2EZ: Spent more then half the wave duration at over 80% health.
	// I Prefer Rum: More then 4 pickups not collected at the end of a wave.
	// Bullet Storm: Wave completed in less then 2 minutes.

	// Score:
	// Enemies killed.
	// Enemies killed by headshot.
	// Enemies killed while airborne.
	// Enemies killed with hazards.
	// Total time spent airborne.
	// Total time spent on the ground.
	// Number of elites killed.
	// Number of snipers/towers disabled.
	// Run completion time.

	// Assorted Fun Stats:
	// Fastest wave.
	// Slowest wave.
	// Total distance travelled.
	// Most distance travelled in a wave.
	// Least distance travelled in a wave.
	// Most shots fired in a wave.
	// Least shots fired in a wave.
	
};
