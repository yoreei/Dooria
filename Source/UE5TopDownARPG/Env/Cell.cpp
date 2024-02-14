// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cell.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

ADooriaCell::ADooriaCell() {};
ADooriaCell::ADooriaCell(int32 _X, int32 _Y, int32 _WallTileType) : X{ _X }, Y{ _Y }, WallTileType{ _WallTileType } {};

void ADooriaCell::BeginPlay()
{
	Super::BeginPlay();
}
