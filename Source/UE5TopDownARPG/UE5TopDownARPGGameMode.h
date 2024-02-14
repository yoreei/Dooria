// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE5TopDownARPGGameMode.generated.h"

using FCell = TPair<int32, int32>;

UCLASS(minimalapi)
class AUE5TopDownARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE5TopDownARPGGameMode();

	void EndGame(bool IsWin);

	void GenerateMaze(int32 rows, int32 cols);

	void InitializeMaze(int32 rows, int32 cols);

	bool IsValidCell(int32 row, int32 col, int32 rows, int32 cols);

	TArray<FCell> GetUnvisitedNeighbors(const FCell& cell, int32 rows, int32 cols);

	void RemoveWall(FCell& current, FCell& next);

	void GetRandPerimPoints(int32 rows, int32 cols, TArray<FCell>& output, int32 num);

	void SpawnMaze();

	void SpawnPlayerAtGridLoc(int i, int j);

	void SpawnDoorAtGridLoc(int i, int j);

	void SpawnWallAtGridLoc(int i, int j);

	AActor* BasicSpawn(int i, int j, TSubclassOf<AActor> SpawnClass);

	FRotator CalculateRotation(int i, int j);

	FVector CalculateUELocation(int i, int j);
	
	void StartPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> WallClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> CharacterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> Friend1Class;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> Friend2Class;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> Enemy1Class;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> Enemy2Class;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> DoorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> EdgeDecoClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	int32 MustOpenDoorsToWin = 3;

	TArray<TArray<TCHAR>> Maze;
};



