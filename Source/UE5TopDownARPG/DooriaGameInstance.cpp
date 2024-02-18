// Fill out your copyright notice in the Description page of Project Settings.

#include "DooriaGameInstance.h"
#include "CoreMinimal.h"
#include "DooriaGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UE5TopDownARPGHUD.h"
#include "UE5TopDownARPG.h"


void UDooriaGameInstance::EndGame(bool IsWin)
{
    AHUD* MyHUD = GetWorld()->GetFirstPlayerController()->GetHUD();
    AUE5TopDownARPGHUD* HUD = Cast<AUE5TopDownARPGHUD>(MyHUD);
    if (IsValid(HUD))
    {
        HUD->ShowEndGameScreen(IsWin);
    }
    else
    {
        ensureMsgf(false, TEXT("No HUD"));
        return;
    }
}

void UDooriaGameInstance::RestartGame()
{
    CurrentLevel = 0;
    AdvanceLevel();
}

int UDooriaGameInstance::GetLevelRows()
{
    return BaseLevelRows + (CurrentLevel - 1) * IncLevelRows;
}

int UDooriaGameInstance::GetLevelCols()
{
    return BaseLevelCols + (CurrentLevel - 1) * IncLevelCols;
}

float UDooriaGameInstance::GetTrapSpawnFactor()
{
    return BaseTrapSpawnFactor + (CurrentLevel - 1) * IncTrapSpawnFactor;
}

void UDooriaGameInstance::AdvanceLevel()
{
    CurrentLevel++;
    if (CurrentLevel >= ReachLevelToWin)
    {
        EndGame(true);
        return;
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