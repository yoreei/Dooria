// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGGameMode.h"
#include "UE5TopDownARPGPlayerController.h"
#include "UE5TopDownARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UE5TopDownARPG.h"
#include "Env/Cell.h"
#include "Env/Door.h"
#include "Maze.h"
#include "Trigger/FloorTrapTrigger.h"
//#include "CrowdPF/Public/CrowdPF.h"
#include "DooriaGameInstance.h"

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include <cstdlib> // For srand() and rand()
#include <ctime> // For time
#include <map>


template<typename T>
using TStack = TArray<T>;

void AUE5TopDownARPGGameMode::InitializeMaze(int32 rows, int32 cols) {
    Maze.Empty();
    Maze.Reserve(rows);
    for (int32 i = 0; i < rows; ++i) {
        TArray<MazeCell> row;
        row.Reserve(cols);
        for (int32 j = 0; j < cols; ++j) {
            row.Add(i % 2 != 0 && j % 2 != 0 ? MazeCell(CellType::NONE) : MazeCell(CellType::Wall));
        }
        Maze.Add(row);
    }
}

// Check if a cell is within bounds
bool AUE5TopDownARPGGameMode::IsValidCell(int32 row, int32 col, int32 rows, int32 cols) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

bool AUE5TopDownARPGGameMode::IsInMaze(int32 row, int32 col, int32 rows, int32 cols) {
    return row >= 1 && row < rows - 1 && col >= 1 && col < cols - 1;
}

// Get all unvisited neighbors of a cell
TArray<FCell> AUE5TopDownARPGGameMode::GetUnvisitedNeighbors(const FCell& cell, int32 rows, int32 cols) {
    TArray<FCell> neighbors;
    const int32 directions[4][2] = { {0, 2}, {2, 0}, {0, -2}, {-2, 0} };

    for (const auto& dir : directions) {
        int32 newRow = cell.Key + dir[0], newCol = cell.Value + dir[1];
        if (IsInMaze(newRow, newCol, rows, cols) && Maze[newRow][newCol].Type == CellType::NONE) {
            neighbors.Add(FCell(newRow, newCol));
        }
    }
    return neighbors;
}

// Remove the wall between two cells
void AUE5TopDownARPGGameMode::RemoveWall(FCell& current, FCell& next) {
    int32 wallRow = (current.Key + next.Key) / 2;
    int32 wallCol = (current.Value + next.Value) / 2;
    Maze[wallRow][wallCol].Type = CellType::Path;
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

void AUE5TopDownARPGGameMode::GetAllCellsPred(std::function<bool(int, int)> Pred, TArray<FCell>& PotentialLoops)
{
    for (int row = 1; row < Maze.Num() - 1 ; ++row)
    {
        for (int col = 1; col < Maze[0].Num() - 1; ++col)
        {
            if (Pred(row, col))
            {
                PotentialLoops.Add(FCell(row, col));
            }
        }
    }
}

void AUE5TopDownARPGGameMode::GenerateMaze(int32 rows, int32 cols) {
    // Depth-First Search with Backtracking
    {
        srand(time(nullptr));
        TStack<FCell> stack;

        Maze[1][1].Type = CellType::Path;
        stack.Push(FCell(1, 1));

        while (!stack.IsEmpty()) {
            FCell currentCell = stack.Pop();

            auto neighbors = GetUnvisitedNeighbors(currentCell, rows, cols);
            if (neighbors.Num() > 0) {
                stack.Push(currentCell);

                FCell chosenNeighbor = neighbors[FMath::RandRange(0, neighbors.Num() - 1)];
                RemoveWall(currentCell, chosenNeighbor);
                Maze[chosenNeighbor.Key][chosenNeighbor.Value].Type = CellType::Path;
                stack.Push(chosenNeighbor);
            }
        }
    }

    // Add Loops in Maze
    {
        TArray<FCell> PotentialLoops;
        GetAllCellsPred([this](int row, int col) -> bool {
            return Maze[row][col].Type == CellType::Wall &&
                (
                    Maze[row - 1][col].Type == CellType::Path && Maze[row + 1][col].Type == CellType::Path
                    ||
                    Maze[row][col - 1].Type == CellType::Path && Maze[row][col + 1].Type == CellType::Path
                    );
            }, PotentialLoops);

        int NumLoops = ((Maze.Num() + Maze[0].Num()) / 5) * LoopinessFactor;
        TArray<FCell> Loops;
        GetRandom(NumLoops, PotentialLoops, Loops);

        for (auto& Cell : Loops)
        {
            Maze[Cell.Key][Cell.Value].Type = CellType::Path;
        }
    }

    // Generate Start
    {
        int32 middleCol = cols / 2;
        // Ensure middleCol is odd. If it's even, decrement by 1.
        if (middleCol % 2 == 0)
        {
            middleCol--;
        }
        Maze[0][middleCol].Type = CellType::Path;
        Maze[0][middleCol].isPlayerStart = true;
    }

    // Generate Doors
    {
        TArray<FCell> doors;
        CalculateDoorLocations(FCell(0, cols / 2), 3, doors);

        int32 doorIdx = 1;
        for (const auto& door : doors) {
            Maze[door.Key][door.Value].Type = CellType::Path;
            Maze[door.Key][door.Value].hasDoor = true;
        }
    }

    // Generate Traps
    {
        TArray<FCell> PotentialTraps;
        GetAllCellsPred([this](int row, int col) -> bool {
            return Maze[row][col].Type == CellType::Path &&
                (
                    Maze[row - 1][col].Type == CellType::Path && Maze[row + 1][col].Type == CellType::Path
                    ||
                    Maze[row][col - 1].Type == CellType::Path && Maze[row][col + 1].Type == CellType::Path
                    );
            }, PotentialTraps);

        UDooriaGameInstance* DooriaGameInstance = Cast<UDooriaGameInstance>(GetWorld()->GetGameInstance());
        if (!IsValid(DooriaGameInstance))
        {
            ensureMsgf(false, TEXT("DooriaGameInstance is not valid."));
            return;
        }

        float fact = DooriaGameInstance->GetTrapSpawnFactor();
        float basetraps = (Maze.Num() + Maze[0].Num());
        int NumTraps = floor(basetraps * fact);
        TArray<FCell> Traps;
        GetRandom(NumTraps, PotentialTraps, Traps);

        for (auto& Cell : Traps)
        {
            Maze[Cell.Key][Cell.Value].hasTrap = true;
        }
    }
}

void AUE5TopDownARPGGameMode::GenerateLightSources() {
    using namespace Side;
    // Essential Lighting

    // Bottom Data Takes Precedence
    TArray<TTuple<int32, int32, FString>> LightSourcePlaces = {
        /* Must be Path:     |    Must be Wall       | Light Source Placement */
        //{N | S | E,        /*|*/ W | DIAG,         /*|*/ "W" }, // T - Cross
        //{N | S | W,        /*|*/ E | DIAG,         /*|*/ "E" },
        //{W | E | N,        /*|*/ S | DIAG,         /*|*/ "S" },
        //{W | E | S,        /*|*/ N | DIAG,         /*|*/ "N" },
        {NW | NE | E | W,  /*|*/ N,                /*|*/ "N" }, // Outer Corners
        {SW | SE | E | W,  /*|*/ S,                /*|*/ "S" },
        {NW | SW | N | S,  /*|*/ W,                /*|*/ "W" },
        {NE | SE | N | S,  /*|*/ E,                /*|*/ "E" },
        {E,                /*|*/ W | N | S | DIAG, /*|*/ "W" }, // Inner Corners
        {W,                /*|*/ E | N | S | DIAG, /*|*/ "E" },
        {N,                /*|*/ S | W | E | DIAG, /*|*/ "S" },
        {S,                /*|*/ N | W | E | DIAG, /*|*/ "N" }
    };

    TArray<AActor*> FoundActors;
    TArray<ADooriaPath*> PotentialLights;
    TArray<ADooriaPath*> PotentialLightsEx;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADooriaPath::StaticClass(), FoundActors);
    for (auto& Actor : FoundActors)
    {
        ADooriaPath* Path = Cast<ADooriaPath>(Actor);
        if (IsValid(Path) && !Path->HasTrap) {
            PotentialLights.Add(Path);
        }
    }

    for (auto& Path : PotentialLights)
    {
        int32 Walls = Path->WallBitMaskDec;
        int32 Paths = ~Path->WallBitMaskDec;
        
        for (auto& Entry : LightSourcePlaces)
        {
            if ((Paths & Entry.Get<0>()) == Entry.Get<0>())
            {
                if ((Walls & Entry.Get<1>()) == Entry.Get<1>())
                {
                    Path->HasLightSource = LightSourceType::MainLight;
                    Path->LightSourceSide = Entry.Get<2>();
                    break;
                }
            }
            PotentialLightsEx.Add(Path); // Did not add a light here, so consider it for 2nd pass
        }
    }

    TArray<TTuple<int32, int32, FString>> LightSourcePlacesEx = {
        /* Must be Path:     |    Must be Wall       | Light Source Placement */
        {N | S,            /*|*/ W | NW | SW,      /*|*/ "W" }, // Long Wall
        {N | S,            /*|*/ E | NE | SE,      /*|*/ "E" },
        {W | E,            /*|*/ N | NW | NE,      /*|*/ "N" },
        {W | E,            /*|*/ S | SW | SE,      /*|*/ "S" },
    };

    for (auto& Path : PotentialLightsEx)
    {
        int32 Walls = Path->WallBitMaskDec;
        int32 Paths = ~Path->WallBitMaskDec;

        for (auto& Entry : LightSourcePlacesEx)
        {
            if ((Paths & Entry.Get<0>()) == Entry.Get<0>())
            {
                if ((Walls & Entry.Get<1>()) == Entry.Get<1>())
                {
                    Path->HasLightSource = LightSourceType::ExtraLight;
                    Path->LightSourceSide = Entry.Get<2>();
                    break;
                }
            }
        }
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
        DooriaPath->SetWallBitMask(TileType);
        DooriaPath->HasTrap = Maze[i][j].hasTrap;
    }

    if (Maze[i][j].isPlayerStart) {
        ACharacter* SpawnedCharacter = Cast<ACharacter>(BasicSpawn(i, j, CharacterClass));
        if (ensure(SpawnedCharacter))
        {
            //APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
            //if (PlayerController)
            //{
            //    PlayerController->Possess(SpawnedCharacter);
            //}
        }

    }
    if (Maze[i][j].hasDoor) {
        AActor* Actor = BasicSpawn(i, j, DoorClass);
        ADoorTrigger* Door = Cast<ADoorTrigger>(Actor);
        if (ensure(Door))
        {
            FRotator Rotator = CalculateRotation(i, j);
            Door->SetActorRotation(Rotator);
            UE_LOG(LogTemp, Warning, TEXT("Door %s ; Rotation: %s"), *Door->GetActorNameOrLabel(), *Rotator.ToString());
        }
    }

    return DooriaPath;
}

void AUE5TopDownARPGGameMode::SpawnMaze()
{
	for (int32 i = 0; i < Maze.Num(); ++i) {
		for (int32 j = 0; j < Maze[i].Num(); ++j) {
            if (Maze[i][j].Type == CellType::Wall)
            {
                SpawnObstructionAtGridLoc(i, j);
            }

            else if (Maze[i][j].Type == CellType::Path)
            {
                SpawnPathAtGridLoc(i, j);
            }
		}
	}
}

//void AUE5TopDownARPGGameMode::SpawnCamera()
//{
//    // Spawn the camera actor
//    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
//    if (PlayerController)
//    {
//        float MaxX = Maze[0].Num() * CellSize;
//        float MaxY = Maze.Num() * CellSize;
//        float CamX = MaxX / 2;
//        float CamY = 0;
//        float CamZ = FMath::Max(MaxX, MaxY) * CameraZFactor;
//
//        FVector Location = { CamY, CamX, CamZ };
//        FActorSpawnParameters SpawnParams;
//        AActor* CameraActor = GetWorld()->SpawnActor<AActor>(CameraClass, Location, CameraRotator, SpawnParams);
//
//        if (CameraActor)
//        {
//            PlayerController->SetViewTarget(CameraActor);
//        }
//        else
//        {
//            // If not spawning, find your camera actor in the level and set it as the view target
//            // Example: Find your camera actor by tag or name
//        }
//    }
//}

int32 AUE5TopDownARPGGameMode::CalculateWallTileType(int i, int j)
{
    using namespace Side;
    TMap<TPair<int32, int32>, int32> Dirs{
        {{0, 1}, N},
        {{1, 1}, NE},
        {{1, 0}, E},
        {{1, -1}, SE},
        {{0, -1}, S},
        {{-1, -1}, SW},
        {{-1, 0}, W},
        {{-1, 1}, NW}
    };

    int32 Result = 0;

    for (const auto& dir : Dirs) {
        TPair<int32, int32> Coords = dir.Key;
        int32 BitValue = dir.Value;

        int newI = i + Coords.Value;
        int newJ = j + Coords.Key;
        
        if (!IsValidCell(newJ, newI, Maze[0].Num(), Maze.Num()) || Maze[newI][newJ].Type == CellType::Wall)
        {
            Result += BitValue;
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

void AUE5TopDownARPGGameMode::PrintMaze(FString PrintTag)
{
    UE_LOG(LogTemp, Warning, TEXT("%s"), *PrintTag);
    for (const auto& row : Maze) {
        FString RowString;
        for (auto& cell : row) {
            RowString += FString::Printf(TEXT("%c"),
                cell.Type == CellType::Wall ? '#' : 
                cell.hasDoor                ? 'D' :
                cell.hasTrap                ? 'T' :
                cell.isPlayerStart          ? 'S' :
                cell.Type == CellType::Path ? ' ' :
                cell.Type == CellType::NONE ? 'N' : '0'); // 0 should never happen
        }
        UE_LOG(LogTemp, Warning, TEXT("%s"), *RowString);
    }
}

void AUE5TopDownARPGGameMode::StartPlay()
{
    SetupDooria();
	Super::StartPlay();
}

void AUE5TopDownARPGGameMode::SetupDooria()
{
    srand(static_cast<unsigned>(time(nullptr)));
    UWorld* pWorld = GetWorld();
    ensure(pWorld);

    int rows = 0;
    int cols = 0;

    UDooriaGameInstance* DooriaGameInstance = Cast<UDooriaGameInstance>(GetWorld()->GetGameInstance());
    if (IsValid(DooriaGameInstance)){
        rows = DooriaGameInstance->GetLevelRows();
        cols = DooriaGameInstance->GetLevelCols();
    }
    else {
        ensureMsgf(false, TEXT("DooriaGameInstance is not valid."));
        return;
    }

    InitializeMaze(rows, cols);
    PrintMaze("After InitializeMaze:");
    GenerateMaze(rows, cols);
    SpawnMaze();
    GenerateLightSources();
    PrintMaze("After GenerateLightSources");
    //SpawnCamera();

    //FCrowdPFModule* CrowdPFModule = FModuleManager::LoadModulePtr<FCrowdPFModule>("CrowdPF");
    //if (CrowdPFModule)
    //{
    //    Options.CellSize = CellSize;
    //    Options.Rows = rows;
    //    Options.Cols = cols;
    //    CrowdPFModule->Init(pWorld, Options);
    //}
}
