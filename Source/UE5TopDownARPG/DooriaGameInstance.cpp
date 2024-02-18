// Fill out your copyright notice in the Description page of Project Settings.

#include "DooriaGameInstance.h"
#include "CoreMinimal.h"
#include "DooriaGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UE5TopDownARPG.h"


void UDooriaGameInstance::EndGame(bool IsWin)
{
    CurrentLevel = 1;
    CurrentTrapSpawnFactor = BaseTrapSpawnFactor;
    CurrentLevelRows = BaseLevelRows;
    CurrentLevelCols = BaseLevelCols;
    if (IsWin)
    {
        UE_LOG(LogUE5TopDownARPG, Log, TEXT("Win"));
    }
    else
    {
        UE_LOG(LogUE5TopDownARPG, Log, TEXT("Lose"));
    }
}

void UDooriaGameInstance::AdvanceLevel()
{
    CurrentLevel++;
    CurrentTrapSpawnFactor += IncTrapSpawnFactor;
    CurrentLevelRows += IncLevelRows;
    CurrentLevelCols += IncLevelCols;
    if (CurrentLevel == ReachLevelToWin)
    {
        EndGame(true);
    }
    
    UWorld* World = GetWorld();
    if (World != nullptr)
    {
        FName CurrentLevelName = *GetWorld()->GetName();
        UGameplayStatics::OpenLevel(this, CurrentLevelName, true);
    }
}

void UDooriaGameInstance::Init()
{
    if (BaseLevelCols % 2 != 1)
    {
        ensureAlwaysMsgf(false, TEXT("Must be odd!"));
    }
    if (BaseLevelRows % 2 != 1)
    {
        ensureAlwaysMsgf(false, TEXT("Must be odd!"));
    }
    if (IncLevelCols % 2 != 0)
    {
        ensureAlwaysMsgf(false, TEXT("Must be even!"));
    }
    if (IncLevelRows % 2 != 0)
    {
        ensureAlwaysMsgf(false, TEXT("Must be even!"));
    }
}