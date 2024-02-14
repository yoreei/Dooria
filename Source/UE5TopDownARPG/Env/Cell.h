// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Cell.generated.h"

UCLASS(Blueprintable)
class ADooriaCell : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	int32 X;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	int32 Y;
};

UENUM(BlueprintType)
enum class EObstructionType : uint8 {
	Wall UMETA(DisplayName = "Wall"),
	Water UMETA(DisplayName = "Water"),
	Lava UMETA(DisplayName = "Lava")
};

UCLASS(Blueprintable)
class ADooriaObstruction : public ADooriaCell
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	EObstructionType ObstructionType;
};

UCLASS(Blueprintable)
class ADooriaPath : public ADooriaCell
{
	GENERATED_BODY()

public:
	/*
000001 - TopLeft (1)
000010 - TopRight (2)
000011 - TopLeftRight (3)
000100 - BottomRight (4)
000101 - TopLeftBottomRight (5)
000110 - TopRightBottomRight (6)
000111 - (7)
001000 - (8)
001001 - (9)
001010 - (10)
001011 - (11)
001100 - (12)
001101 - (13)
001110 - (14)
001111 - (15)
010000 - (16)
010001 - (17)
010010 - (18)
010011 - (19)
010100 - (20)
010101 - (21)
010110 - (22)
010111 - (23)
011000 - (24)
011001 - (25)
011010 - (26)
011011 - (27)
011100 - (28)
011101 - (29)
011110 - (30)
011111 - (31)
100000 - (32)
100001 - (33)
100010 - (34)
100011 - (35)
100100 - (36)
100101 - (37)
100110 - (38)
100111 - (39)
101000 - (40)
101001 - (41)
101010 - (42)
101011 - (43)
101100 - (44)
101101 - (45)
101110 - (46)
101111 - (47)
110000 - (48)

	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	int32 WallBitMask;
};