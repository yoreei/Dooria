// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DooriaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UDooriaGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Dooria|Levels")
	void AdvanceLevel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dooria|MazeGen")
	float BaseTrapSpawnFactor = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dooria|MazeGen")
	float IncTrapSpawnFactor = 0.2f;

	UPROPERTY(BlueprintReadOnly, Category = "Dooria|MazeGen")
	float CurrentTrapSpawnFactor = BaseTrapSpawnFactor;

	UPROPERTY(BlueprintReadWrite, Category = "Dooria|Levels")
	int32 ReachLevelToWin = 4;

	UPROPERTY(BlueprintReadWrite, Category = "Dooria|Levels")
	int32 CurrentLevel = 1;

	UFUNCTION(BlueprintCallable, Category = "Dooria|Levels")
	void EndGame(bool IsWin);
};
