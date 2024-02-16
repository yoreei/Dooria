// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

using FCell = TPair<int32, int32>; // Key = Y, Value = X

template<typename T>
void GetRandom(int Num, TArray<T>& InArray, TArray<T>& OutArray)
{
	ensure(Num <= InArray.Num());
	TArray<int> UniqueList;
	while (Num > 0)
	{
		int32 RandIdx = FMath::RandRange(0, InArray.Num() - 1);
		if (!UniqueList.Contains(RandIdx))
		{
			OutArray.Add(InArray[RandIdx]);
			UniqueList.Add(RandIdx);
		}
		Num--;
	}
}