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
	ADooriaCell();
	ADooriaCell(int32 _X, int32 _Y, int32 _WallTileType);

	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Dooria")
	int32 X;

	UPROPERTY(BlueprintReadOnly, Category = "Dooria")
	int32 Y;

	UPROPERTY(BlueprintReadOnly, Category = "Dooria")
	int32 WallTileType;

	// UFUNCTION()
	// void TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigateBy, AActor* DamageCauser);

};

