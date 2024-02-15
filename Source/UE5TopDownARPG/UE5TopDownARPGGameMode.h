// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Env/Cell.h"
#include "UE5TopDownARPGGameMode.generated.h"

using FCell = TPair<int32, int32>; // Key = Y, Value = X
UCLASS(minimalapi)
class AUE5TopDownARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE5TopDownARPGGameMode();

	// GamePlay Methods 

	void EndGame(bool IsWin);

	// Generate Methods

	void GenerateMaze(int32 rows, int32 cols);

	void InitializeMaze(int32 rows, int32 cols);

	bool IsValidCell(int32 row, int32 col, int32 rows, int32 cols);

	TArray<FCell> GetUnvisitedNeighbors(const FCell& cell, int32 rows, int32 cols);

	void RemoveWall(FCell& current, FCell& next);

	void CalculateDoorLocations(FCell start, int32 num, TArray<FCell>& output);

	// Spawn Methods

	void SpawnMaze();

	void SpawnPlayerAtGridLoc(int i, int j);

	void SpawnDoorAtGridLoc(int i, int j);

	void SpawnFloorTrapAtGridLoc(int i, int j);

	ADooriaObstruction* SpawnObstructionAtGridLoc(int i, int j);

	ADooriaCell* SpawnCellAtGridLoc(int i, int j, TSubclassOf<AActor> SpawnClass);

	ADooriaPath* SpawnPathAtGridLoc(int i, int j);

	AActor* BasicSpawn(int i, int j, TSubclassOf<AActor> SpawnClass);

	FRotator CalculateRotation(int i, int j);

	int32 CalculateWallTileType(int i, int j);

	FVector CalculateUELocation(int i, int j);

	// GameMode
	
	void StartPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> WallClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> DoorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> PathClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> CharacterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> SwordFloorTrapClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> FlameFloorTrapClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> GeiserFloorTrapClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> BoulderFloorTrapClass;
	
	//UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	//TSubclassOf<AActor> Friend1Class;

	//UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	//TSubclassOf<AActor> Friend2Class;

	//UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	//TSubclassOf<AActor> Enemy1Class;

	//UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	//TSubclassOf<AActor> Enemy2Class;

	//UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	//TSubclassOf<AActor> EdgeDecoClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	int32 MustOpenDoorsToWin = 3;

	TArray<TArray<TCHAR>> Maze;
};



