// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Containers/BitArray.h"
#include "Cell.generated.h"

enum class Side : int32 {
	NONE = 0b00000000,
	N = 0b00000001,
	NE = 0b00000010,
	E = 0b00000100,
	SE = 0b00001000,
	S = 0b00010000,
	SW = 0b00100000,
	W = 0b01000000,
	NW = 0b10000000
};

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

	// Setters

	void setWallBitMask(int Val);

	/*
		NONE = 0b 0000 0000,
		N =    0b 0000 0001,
		NE =   0b 0000 0010,
		E =    0b 0000 0100,
		SE =   0b 0000 1000,
		S =    0b 0001 0000,
		SW =   0b 0010 0000,
		W =    0b 0100 0000,
		NW =   0b 1000 0000
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	int32 WallBitMaskDec;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	//std::bitset<32> WallBitMaskBin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	FString WallBitMaskBin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	bool N;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	bool NE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	bool E;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	bool SE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	bool S;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	bool SW;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	bool W;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dooria")
	bool NW;
};