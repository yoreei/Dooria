// Fill out your copyright notice in the Description page of Project Settings.

#include "DooriaGameInstance.h"
#include "CoreMinimal.h"
#include "DooriaGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UE5TopDownARPG.h"


void UDooriaGameInstance::EndGame(bool IsWin)
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

void UDooriaGameInstance::AdvanceLevel()
{
    CurrentLevel++;
    CurrentTrapSpawnFactor += IncTrapSpawnFactor;
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