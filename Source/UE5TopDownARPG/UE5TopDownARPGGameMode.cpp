// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGGameMode.h"
#include "UE5TopDownARPGPlayerController.h"
#include "UE5TopDownARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UE5TopDownARPG.h"
#include "Env/Cell.h"
#include "Env/Door.h"
#include "Trigger/FloorTrapTrigger.h"

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include <cstdlib> // For srand() and rand()
#include <ctime> // For time
#include <map>


template<typename T>
using TStack = TArray<T>;
const static float CellSize = 100.0f; // Unreal units per cell

// Initialize the Maze with walls ('#') and cells (' ')
void AUE5TopDownARPGGameMode::InitializeMaze(int32 rows, int32 cols) {
    Maze.Empty();
    Maze.Reserve(rows);
    for (int32 i = 0; i < rows; ++i) {
        TArray<TCHAR> row;
        row.Reserve(cols);
        for (int32 j = 0; j < cols; ++j) {
            row.Add(i % 2 != 0 && j % 2 != 0 ? ' ' : '#');
        }
        Maze.Add(row);
    }
}

// Check if a cell is within bounds
bool AUE5TopDownARPGGameMode::IsValidCell(int32 row, int32 col, int32 rows, int32 cols) {
    return row >= 1 && row < rows && col >= 1 && col < cols;
}

// Get all unvisited neighbors of a cell
TArray<FCell> AUE5TopDownARPGGameMode::GetUnvisitedNeighbors(const FCell& cell, int32 rows, int32 cols) {
    TArray<FCell> neighbors;
    const int32 directions[4][2] = { {0, 2}, {2, 0}, {0, -2}, {-2, 0} };

    for (const auto& dir : directions) {
        int32 newRow = cell.Key + dir[0], newCol = cell.Value + dir[1];
        if (IsValidCell(newRow, newCol, rows, cols) && Maze[newRow][newCol] == ' ') {
            neighbors.Add(FCell(newRow, newCol));
        }
    }
    return neighbors;
}

// Remove the wall between two cells
void AUE5TopDownARPGGameMode::RemoveWall(FCell& current, FCell& next) {
    int32 wallRow = (current.Key + next.Key) / 2;
    int32 wallCol = (current.Value + next.Value) / 2;
    Maze[wallRow][wallCol] = ' ';
}

// Randomly select perimeter points
void AUE5TopDownARPGGameMode::CalculateDoorLocations(FCell start, int32 num, TArray<FCell>& output) {
    // TODO Do not assume that start is 0, cols/2

    int32 cols = Maze.Num();
    int32 rows = Maze[0].Num();
    TArray<FCell> perimPositions;
    for (int32 col = 1; col < cols; col += 4) {
        perimPositions.Add(FCell(rows - 1, col));
    }
    for (int32 row = rows/ 2; row < rows; row += 4) {
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

// Depth-First Search with Backtracking to generate Maze paths
void AUE5TopDownARPGGameMode::GenerateMaze(int32 rows, int32 cols) {
    srand(time(nullptr));
    TStack<FCell> stack;

    Maze[1][1] = 'V';
    stack.Push(FCell(1, 1));

    while (!stack.IsEmpty()) {
        FCell currentCell = stack.Pop();

        auto neighbors = GetUnvisitedNeighbors(currentCell, rows, cols);
        if (neighbors.Num() > 0) {
            stack.Push(currentCell); // Push current cell back to stack

            FCell chosenNeighbor = neighbors[FMath::RandRange(0, neighbors.Num() - 1)];
            RemoveWall(currentCell, chosenNeighbor);
            Maze[chosenNeighbor.Key][chosenNeighbor.Value] = 'V';
            stack.Push(chosenNeighbor);
        }
    }

    // Reset visited cells to empty spaces
    for (int32 i = 1; i < rows; i += 2) {
        for (int32 j = 1; j < cols; j += 2) {
            if (Maze[i][j] == 'V') Maze[i][j] = ' ';
        }
    }

    // Add Loops in Maze With Traps

    for (int row = 2; row < Maze.Num(); row += 4)
    {
        int32 randCol;
        do
        {
            randCol = FMath::RandRange(0, Maze[0].Num() - 1);
        } while (Maze[row][randCol] != '#');

        Maze[row][randCol] = 'T';
    }

    // Generate Start
    Maze[0][cols / 2] = '0';

    // Generate Doors
    TArray<FCell> doors;
    CalculateDoorLocations(FCell(0, cols / 2), 3, doors);

    int32 doorIdx = 1;
    for (const auto& door : doors) {
        Maze[door.Key][door.Value] = '0' + doorIdx;
        doorIdx++;
    }

    // TODO Spawn Traps
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

ADooriaCell* AUE5TopDownARPGGameMode::SpawnCellAtGridLoc(int i, int j, TSubclassOf<AActor> SpawnClass)
{
    AActor* Actor = BasicSpawn(i, j, SpawnClass);
    ADooriaCell* DooriaCell = Cast<ADooriaCell>(Actor);
    if (ensure(DooriaCell))
    {
        DooriaCell->X = j;
        DooriaCell->Y = i;
    }
    return DooriaCell;
}

ADooriaPath* AUE5TopDownARPGGameMode::SpawnPathAtGridLoc(int i, int j)
{
    ADooriaCell* Cell = SpawnCellAtGridLoc(i,j, PathClass);
    ADooriaPath* DooriaPath = Cast<ADooriaPath>(Cell);
    if (ensure(DooriaPath))
    {
        int TileType = CalculateWallTileType(i, j);
        DooriaPath->setWallBitMask(TileType);
    }
    return DooriaPath;
}

void AUE5TopDownARPGGameMode::SpawnFloorTrapAtGridLoc(int i, int j)
{
    TArray<TSubclassOf<AActor>> TrapType = { SwordFloorTrapClass, FlameFloorTrapClass, GeiserFloorTrapClass, BoulderFloorTrapClass };
    int32 RandIdx = FMath::RandRange(0, TrapType.Num() - 1);
    auto RandTrapClass = TrapType[RandIdx];

    AActor* Actor = BasicSpawn(i, j, TrapType[RandIdx]);
    AFloorTrapTrigger* Trap = Cast<AFloorTrapTrigger>(Actor);
    if (ensure(Trap))
    {
        FRotator Rotator = CalculateRotation(i, j);
        Trap->SetActorRotation(Rotator);
        UE_LOG(LogTemp, Warning, TEXT("Spawning Trap %s"), *Trap->GetActorNameOrLabel());
    }
}

void AUE5TopDownARPGGameMode::SpawnMaze()
{
	for (int32 i = 0; i < Maze.Num(); ++i) {
		for (int32 j = 0; j < Maze[i].Num(); ++j) {
            if (Maze[i][j] == '#')
            {
                SpawnObstructionAtGridLoc(i, j);
            }

            else if (Maze[i][j] == ' ')
            {
                SpawnPathAtGridLoc(i, j);
            }

            else if (Maze[i][j] == '0') {
                SpawnPathAtGridLoc(i, j);
                SpawnPlayerAtGridLoc(i,j);

            }
            else if (Maze[i][j] >= '1' && Maze[i][j] <= '9') {
                SpawnPathAtGridLoc(i, j);
                SpawnDoorAtGridLoc(i,j);
            }

            else if (Maze[i][j] == 'T') {
                SpawnPathAtGridLoc(i, j);
                SpawnFloorTrapAtGridLoc(i, j);
            }
		}
	}
}

int32 AUE5TopDownARPGGameMode::CalculateWallTileType(int i, int j)
{
    TMap<TPair<int32, int32>, Side> Dirs{
        {{0, 1}, Side::N},
        {{1, 1}, Side::NE},
        {{1, 0}, Side::E},
        {{1, -1}, Side::SE},
        {{0, -1}, Side::S},
        {{-1, -1}, Side::SW},
        {{-1, 0}, Side::W},
        {{-1, 1}, Side::NW}
    };

    int32 Result = 0;

    for (const auto& dir : Dirs) {
        TPair<int32, int32> Coords = dir.Key;
        Side BitValue = dir.Value;

        int newI = i + Coords.Value;
        int newJ = j + Coords.Key;
        
        if (!IsValidCell(newJ, newI, Maze[0].Num(), Maze.Num()) || Maze[newI][newJ] == '#')
        {
            Result += static_cast<int>(BitValue);
        }
    }

    return Result;
}

AActor* AUE5TopDownARPGGameMode::BasicSpawn(int i, int j, TSubclassOf<AActor> SpawnClass)
{
    FActorSpawnParameters SpawnParameters;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    FVector Location = CalculateUELocation(i, j);
    FRotator Rotation(0.f, 0.f, 0.f);
    AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnClass, Location, Rotation, SpawnParameters);
    return SpawnedActor;
}

ADooriaObstruction* AUE5TopDownARPGGameMode::SpawnObstructionAtGridLoc(int i, int j)
{
    AActor* Actor = SpawnCellAtGridLoc(i, j, WallClass);
    ADooriaObstruction* Obstruction = Cast<ADooriaObstruction>(Actor);

    if (ensure(Obstruction))
    {
        Obstruction->ObstructionType = EObstructionType::Wall;
    }

    return Obstruction;
}

void AUE5TopDownARPGGameMode::SpawnPlayerAtGridLoc(int i, int j)
{
    ACharacter* SpawnedCharacter = Cast<ACharacter>(BasicSpawn(i, j, CharacterClass));
    if (ensure(SpawnedCharacter))
    {
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
        if (PlayerController)
        {
            PlayerController->Possess(SpawnedCharacter);
        }
    }
}

void AUE5TopDownARPGGameMode::SpawnDoorAtGridLoc(int i, int j)
{
    AActor* Actor = BasicSpawn(i, j, DoorClass);
    ADoorTrigger* Door = Cast<ADoorTrigger>(Actor);
    if (ensure(Door))
    {
        FRotator Rotator = CalculateRotation(i, j);
        Door->SetActorRotation(Rotator);
        UE_LOG(LogTemp, Warning, TEXT("Door %s ; Rotation: %s"), *Door->GetActorNameOrLabel(), *Rotator.ToString());
    }
}

FRotator AUE5TopDownARPGGameMode::CalculateRotation(int i, int j)
{
    if (Maze.Num() - 1 == i)
    {
        UE_LOG(LogTemp, Warning, TEXT("rotation 0"));
        return FRotator(0.f, 90.f, 0.f);
    }
    else if (Maze[0].Num() - 1 == j)
    {
        UE_LOG(LogTemp, Warning, TEXT("rotation 90"));
        return FRotator(0.f, 180.f, 0.f);
    }
    else if (0 == i)
    {
        UE_LOG(LogTemp, Warning, TEXT("rotation 180"));
        return FRotator(0.f, 270.f, 0.f);
    }
    else if (0 == j)
    {
        UE_LOG(LogTemp, Warning, TEXT("rotation 270"));
        return FRotator(0.f, 0.f, 0.f);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Won't Calculate Rotation for loc %d %d"), i, j);
        return FRotator(0.f, 0.f, 0.f);
    }
}

FVector AUE5TopDownARPGGameMode::CalculateUELocation(int i, int j)
{
    return FVector(i * CellSize, j * CellSize, 0);
}


void AUE5TopDownARPGGameMode::StartPlay()
{
    srand(static_cast<unsigned>(time(nullptr)));
    UWorld* pWorld = GetWorld();
    ensure(pWorld);

    int32 rows = 21; // Must be odd
    int32 cols = 21; // Must be odd

    InitializeMaze(rows, cols);
    GenerateMaze(rows, cols);
    SpawnMaze();

    // Print the Maze
    for (const auto& row : Maze) {
        FString RowString;
        for (TCHAR cell : row) {
            RowString += FString::Printf(TEXT("%c"), cell);
        }
        UE_LOG(LogTemp, Warning, TEXT("%s"), *RowString);
    }

	Super::StartPlay();

}



