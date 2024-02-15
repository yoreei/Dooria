// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cell.h"
#include "UObject/ConstructorHelpers.h"
#include <bitset>
#include "Engine/World.h"

void ADooriaCell::BeginPlay()
{
	Super::BeginPlay();
}

FString Int32ToBinaryString(int32 Value)
{
    FString BinaryString = TEXT("");
    for (int32 i = 31; i >= 0; i--)
    {
        // Use bit shifting to check each bit, and append "1" or "0" to the string accordingly
        BinaryString += (Value & (1 << i)) ? TEXT("1") : TEXT("0");

        // Optional: Add a space every 4 bits for readability
        if (i % 4 == 0 && i != 0)
        {
            BinaryString += TEXT(" ");
        }
    }
    return BinaryString;
}

void ADooriaPath::setWallBitMask(int32 Val)
{
	WallBitMaskDec = Val;
    WallBitMaskBin = Int32ToBinaryString(Val);
    N = (Val & static_cast<int32>(Side::N)) != 0;
    NE = (Val & static_cast<int32>(Side::NE)) != 0;
    E = (Val & static_cast<int32>(Side::E)) != 0;
    SE = (Val & static_cast<int32>(Side::SE)) != 0;
    S = (Val & static_cast<int32>(Side::S)) != 0;
    SW = (Val & static_cast<int32>(Side::SW)) != 0;
    W = (Val & static_cast<int32>(Side::W)) != 0;
    NW = (Val & static_cast<int32>(Side::NW)) != 0;
}
