// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGGameMode.h"
#include "UE5TopDownARPGPlayerController.h"
#include "UE5TopDownARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UE5TopDownARPG.h"

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include <cstdlib> // For srand() and rand()
#include <ctime> // For time

using FCell = TPair<int32, int32>;
template<typename T>
using TStack = TArray<T>;

// Initialize the maze with walls ('#') and cells (' ')
void InitializeMaze(TArray<TArray<TCHAR>>& maze, int32 rows, int32 cols) {
    maze.Empty();
    maze.Reserve(rows);
    for (int32 i = 0; i < rows; ++i) {
        TArray<TCHAR> row;
        row.Reserve(cols);
        for (int32 j = 0; j < cols; ++j) {
            row.Add(i % 2 != 0 && j % 2 != 0 ? ' ' : '#');
        }
        maze.Add(row);
    }
}

// Check if a cell is valid and unvisited
bool IsValidCell(int32 row, int32 col, int32 rows, int32 cols, const TArray<TArray<TCHAR>>& maze) {
    return row >= 1 && row < rows && col >= 1 && col < cols && maze[row][col] == ' ';
}

// Get all unvisited neighbors of a cell
TArray<FCell> GetUnvisitedNeighbors(const FCell& cell, const TArray<TArray<TCHAR>>& maze, int32 rows, int32 cols) {
    TArray<FCell> neighbors;
    const int32 directions[4][2] = { {0, 2}, {2, 0}, {0, -2}, {-2, 0} };

    for (const auto& dir : directions) {
        int32 newRow = cell.Key + dir[0], newCol = cell.Value + dir[1];
        if (IsValidCell(newRow, newCol, rows, cols, maze)) {
            neighbors.Add(FCell(newRow, newCol));
        }
    }
    return neighbors;
}

// Remove the wall between two cells
void RemoveWall(FCell& current, FCell& next, TArray<TArray<TCHAR>>& maze) {
    int32 wallRow = (current.Key + next.Key) / 2;
    int32 wallCol = (current.Value + next.Value) / 2;
    maze[wallRow][wallCol] = ' ';
}

// Randomly select perimeter points
void GetRandPerimPoints(int32 rows, int32 cols, TArray<FCell>& output, int32 num) {
    srand(static_cast<unsigned>(time(nullptr)));

    TArray<FCell> perimPositions;
    for (int32 col = 1; col < cols; col += 2) {
        perimPositions.Add(FCell(0, col));
        perimPositions.Add(FCell(rows - 1, col));
    }
    for (int32 row = 1; row < rows; row += 2) {
        perimPositions.Add(FCell(row, 0));
        perimPositions.Add(FCell(row, cols - 1));
    }

    num = FMath::Min(num, perimPositions.Num());
    while (output.Num() < num) {
        int32 randIndex = FMath::RandRange(0, perimPositions.Num() - 1);
        if (!output.Contains(perimPositions[randIndex])) {
            output.Add(perimPositions[randIndex]);
        }
    }
}

// Depth-First Search with Backtracking to generate maze paths
void GenerateMaze(TArray<TArray<TCHAR>>& maze, int32 rows, int32 cols) {
    srand(time(nullptr)); // Seed random number generator
    TStack<FCell> stack;
    TArray<FCell> doors;

    maze[1][1] = 'V';
    stack.Push(FCell(1, 1));

    while (!stack.IsEmpty()) {
        FCell currentCell = stack.Pop();

        auto neighbors = GetUnvisitedNeighbors(currentCell, maze, rows, cols);
        if (neighbors.Num() > 0) {
            stack.Push(currentCell); // Push current cell back to stack

            FCell chosenNeighbor = neighbors[FMath::RandRange(0, neighbors.Num() - 1)];
            RemoveWall(currentCell, chosenNeighbor, maze);
            maze[chosenNeighbor.Key][chosenNeighbor.Value] = 'V';
            stack.Push(chosenNeighbor);
        }
    }

    // Reset visited cells to empty spaces
    for (int32 i = 1; i < rows; i += 2) {
        for (int32 j = 1; j < cols; j += 2) {
            if (maze[i][j] == 'V') maze[i][j] = ' ';
        }
    }

    GetRandPerimPoints(rows, cols, doors, 4);

    int32 doorIdx = 0;
    for (const auto& door : doors) {
        maze[door.Key][door.Value] = '0' + TCHAR(doorIdx);
        doorIdx++;
    }
}

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

void AUE5TopDownARPGGameMode::SpawnMaze(const TArray<TArray<TCHAR>>& maze)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const float CellSize = 100.0f; // Unreal units per cell

	for (int32 i = 0; i < maze.Num(); ++i) {
		for (int32 j = 0; j < maze[i].Num(); ++j) {
            FVector Location(j * CellSize, i * CellSize, 0.f);
            FRotator Rotation(0.f, 0.f, 0.f);
			if (maze[i][j] == '#') {
				AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(WallClass, Location, Rotation, SpawnParameters);
				ensure(SpawnedActor); // Ensure the actor was spawned
			}
            else if (maze[i][j] == '0') {
                //
                SpawnPlayerAtLocation(Location, Rotation);

            }
            else if (maze[i][j] >= '1' && maze[i][j] <= '9') {
                //
            }
		}
	}
}

void AUE5TopDownARPGGameMode::SpawnPlayerAtLocation(const FVector& Location, const FRotator& Rotation)
{
    // Path to your Blueprint character
    FString BlueprintPath = TEXT("Blueprint'/Game/TopDown/Blueprints/BP_TopDownCharacter.BP_TopDownCharacter_C'");

    // Load the Blueprint class
    UClass* BlueprintClass = StaticLoadClass(ACharacter::StaticClass(), nullptr, *BlueprintPath);
    if (BlueprintClass == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot find Blueprint class at %s"), *BlueprintPath);
        return;
    }

    // Set up spawn parameters
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // Spawn the Blueprint character
    ACharacter* SpawnedCharacter = GetWorld()->SpawnActor<ACharacter>(BlueprintClass, Location, Rotation, SpawnParams);

    // Optional: Possess the spawned character with a player controller
    if (SpawnedCharacter != nullptr)
    {
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
        if (PlayerController)
        {
            PlayerController->Possess(SpawnedCharacter);
        }
    }
}


void AUE5TopDownARPGGameMode::StartPlay()
{
	Super::StartPlay();

	UWorld* pWorld = GetWorld();
	ensure(pWorld);

    int32 rows = 21; // Must be odd
    int32 cols = 21; // Must be odd
    TArray<TArray<TCHAR>> maze;

    InitializeMaze(maze, rows, cols);
    GenerateMaze(maze, rows, cols);
    SpawnMaze(maze);

    // Print the maze
    for (const auto& row : maze) {
        FString RowString;
        for (TCHAR cell : row) {
            RowString += FString::Printf(TEXT("%c"), cell);
        }
        UE_LOG(LogTemp, Warning, TEXT("%s"), *RowString);
    }

    //spawnmaze
}



