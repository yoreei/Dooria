// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Env/Cell.h"
#include "Maze.h"
#include "CrowdPF/Public/CrowdPF.h"
#include "UE5TopDownARPGGameMode.generated.h"

UCLASS(minimalapi)
class AUE5TopDownARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE5TopDownARPGGameMode();

	// GamePlay Methods 

	void SetupDooria();

	void EndGame(bool IsWin);

	// Generate Methods

	void GenerateMaze(int32 rows, int32 cols);

	void InitializeMaze(int32 rows, int32 cols);

	bool IsValidCell(int32 row, int32 col, int32 rows, int32 cols);

	bool IsInMaze(int32 row, int32 col, int32 rows, int32 cols);

	TArray<FCell> GetUnvisitedNeighbors(const FCell& cell, int32 rows, int32 cols);

	void RemoveWall(FCell& current, FCell& next);

	void CalculateDoorLocations(FCell start, int32 num, TArray<FCell>& output);

	void GetAllCellsPred(std::function<bool(int, int)> Pred, TArray<FCell>& PotentialLoops);

	void PrintMaze(FString PrintTag);

	void GenerateLightSources();

	// Spawn Methods

	void SpawnMaze();

	void SpawnCamera();

	ADooriaObstruction* SpawnObstructionAtGridLoc(int i, int j);

	ADooriaCell* SpawnCellAtGridLoc(int i, int j, TSubclassOf<AActor> SpawnClass);

	ADooriaPath* SpawnPathAtGridLoc(int i, int j);

	AActor* BasicSpawn(int i, int j, TSubclassOf<AActor> SpawnClass);

	FRotator CalculateRotation(int i, int j);

	int32 CalculateWallTileType(int i, int j);

	FVector CalculateUELocation(int i, int j);

	// GameMode
	
	void StartPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dooria|MazeGen")
	bool CanMoveAnywhere = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dooria|MazeGen")
	TSubclassOf<AActor> WallClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dooria|MazeGen")
	TSubclassOf<AActor> DoorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dooria|MazeGen")
	TSubclassOf<AActor> PathClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dooria|MazeGen")
	TSubclassOf<AActor> CharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dooria|MazeGen")
	TSubclassOf<AActor> FloorTrapClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dooria|MazeGen")
	float LoopinessFactor = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dooria|MazeGen")
	float TrapSpawnFactor = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	TSubclassOf<AActor> CameraClass;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	float CameraZFactor = 1.9;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	FRotator CameraRotator{ -70.f, 0.f, 0.f };

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	float CellSize = 128.f;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	bool UseCrowdPf = false;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	bool DrawDebugPath = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yoreei's Crowd Pathfinder")
	FCrowdPFOptions Options;



	//UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	//TSubclassOf<AActor> FlameFloorTrapClass;

	//UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	//TSubclassOf<AActor> GeiserFloorTrapClass;

	//UPROPERTY(EditDefaultsOnly, Category = "Dooria")
	//TSubclassOf<AActor> BoulderFloorTrapClass;
	
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

	// Levels

	UFUNCTION(BlueprintCallable, Category = "Dooria|Levels")
	void AdvanceLevel();

	UPROPERTY(EditDefaultsOnly, Category = "Dooria|Levels")
	int32 ReachLevelToWin = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Dooria|Levels")
	int32 CurrentLevel = 1;

	TArray<TArray<MazeCell>> Maze;
};



