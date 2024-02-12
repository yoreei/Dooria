// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGGameMode.h"
#include "UE5TopDownARPGPlayerController.h"
#include "UE5TopDownARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UE5TopDownARPG.h"

AUE5TopDownARPGGameMode::AUE5TopDownARPGGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUE5TopDownARPGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void AUE5TopDownARPGGameMode::EndGame(bool IsWin)
{
	if (IsWin)
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("Win"));
	}
	else
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("Lose"));
	}
}

void AUE5TopDownARPGGameMode::generateMaze(TArray<TArray<char>>& maze)
{
	int32 rows = 28;
	int32 cols = 32;
	maze.Empty(); // Clear existing data
	maze.SetNum(rows); // Set number of rows

	for (int32 i = 0; i < rows; ++i) {
		maze[i].SetNum(cols); // Set number of columns for each row
		for (int32 j = 0; j < cols; ++j) {
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
				maze[i][j] = 'W'; // Wall
			}
			else {
				maze[i][j] = '.'; // Empty space
			}
		}
	}
}

void AUE5TopDownARPGGameMode::spawnMaze(const TArray<TArray<char>>& maze)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const float CellSize = 100.0f; // Unreal units per cell

	for (int32 i = 0; i < maze.Num(); ++i) {
		for (int32 j = 0; j < maze[i].Num(); ++j) {
			if (maze[i][j] == 'W') {
				FVector Location(j * CellSize, i * CellSize, 0.f);
				FRotator Rotation(0.f, 0.f, 0.f);
				AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(WallClass, Location, Rotation, SpawnParameters);
				ensure(SpawnedActor); // Ensure the actor was spawned
			}
		}
	}
}



void AUE5TopDownARPGGameMode::StartPlay()
{
	Super::StartPlay();

	UWorld* pWorld = GetWorld();
	ensure(pWorld);
	TArray<TArray<char>> maze;
	generateMaze(maze);
	spawnMaze(maze);
}
