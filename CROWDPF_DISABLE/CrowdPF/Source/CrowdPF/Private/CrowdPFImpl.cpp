﻿// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrowdPFImpl.h"
#include "CrowdPF.h"
#include "Utils.h"

#include "GameFramework/Pawn.h"
#include "Engine/World.h"
// #include "NavigationSystem.h" eh?
#include "Engine/TextRenderActor.h"
#include "Components/TextRenderComponent.h"
#include "Internationalization/Text.h"
#include "Kismet/GameplayStatics.h"

#include "Editor.h"
#include "Editor/EditorEngine.h"

#include <map>
#include <queue>
#include <climits>
#include <cmath>
#include <NavigationData.h>

#define LOCTEXT_NAMESPACE "FCrowdPFModule"

DEFINE_LOG_CATEGORY(LogCrowdPF)

void FCrowdPFModule::StartupModule()
{
	//FEditorDelegates::BeginPIE.AddRaw(this, &FCrowdPFModule::OnBeginPIE);
	FEditorDelegates::EndPIE.AddRaw(this, &FCrowdPFModule::OnEndPIE);
}

void FCrowdPFModule::ShutdownModule()
{
	//FEditorDelegates::BeginPIE.RemoveAll(this);
	FEditorDelegates::EndPIE.RemoveAll(this);
}

//void FCrowdPFModule::OnBeginPIE(bool bIsSimulating)
//{
//	// Reset state here before PIE starts
//}

void FCrowdPFModule::OnEndPIE(bool bIsSimulating)
{
	ModuleImplementation.Reset();
	ModuleImplementation = MakeUnique<Impl>();
}


/* Public Functions */

FCrowdPFModule::FCrowdPFModule() { ModuleImplementation = MakeUnique<FCrowdPFModule::Impl>(); };
FCrowdPFModule::FCrowdPFModule(FCrowdPFModule&&) = default;
FCrowdPFModule::~FCrowdPFModule() = default;
FCrowdPFModule& FCrowdPFModule::operator=(FCrowdPFModule&&) = default;
void FCrowdPFModule::DoFlowTiles(const FVector& WorldOrigin, const FVector& WorldGoal, OUT FNavPathSharedPtr& OutPath) { ModuleImplementation->DoFlowTiles(WorldOrigin, WorldGoal, OutPath); }
void FCrowdPFModule::Init(UWorld* _World, FCrowdPFOptions Options) { ModuleImplementation->Init(_World, Options); } // TODO better handling of World?

float FCrowdPFModule::Impl::toUU(int Val, bool isX)
{
	return (Val * O.CellSize) + (isX ? O.OffsetX : O.OffsetY);
}

bool FCrowdPFModule::Impl::IsWall(const FIntVector2& Cell) const
{
	int Idx = Cell.Y * O.Rows + Cell.X;
	if (ensure(IsValidIdx(Idx)))
	{
		return CostFields[Idx] == UINT8_MAX;
	}
	return false;
}

/* Begin Eikonal */
/*
Ray starts from Origin and extends in opposite direction of Goal
*/
void FCrowdPFModule::Impl::BresenhamsRay2D(const FIntVector2& Goal, FIntVector2 Origin, OUT std::deque<FIntVector2>& LOS)
{
	// Calculate end point - large enough to ensure it goes "off-grid"
	FIntVector2 Direction = (Origin - Goal) * 1000;

	// Bresenham's Algorithm in 2D
	int dx = FMath::Abs(Direction.X - Origin.X), sx = Origin.X < Direction.X ? 1 : -1;
	int dy = -FMath::Abs(Direction.Y - Origin.Y), sy = Origin.Y < Direction.Y ? 1 : -1;
	int err = dx + dy, e2;

	while (IsWall(Origin) == false) {
		// Mark the current cell as blocked
		if (IsInGrid(Origin))
		{
			LOS.push_back(Origin);
		}

		if (Origin.X == Direction.X && Origin.Y == Direction.Y) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; Origin.X += sx; }
		if (e2 <= dx) { err += dx; Origin.Y += sy; }
	}
}

/*
Cell & Goal: Grid Coordinates
*/
void FCrowdPFModule::Impl::GetLos(const FIntVector2& Cell, const FIntVector2& Goal, std::deque<FIntVector2>& Los)
{
	FVector2D GoalToCell = ToVector2D(Cell - Goal);
	bool isDiagonalOrientation = GoalToCell.X * GoalToCell.Y > 0;

	if (isDiagonalOrientation)
	{
		FIntVector2 sideNW = Cell + Dirs::NW;
		if (IsInGrid(sideNW)
			&& !IsWall(sideNW)
			&& !IsWall(Cell + Dirs::W)
			&& !IsWall(Cell + Dirs::N))
		{
			BresenhamsRay2D(Goal + Dirs::S, GoalToCell.Y > 0 ? Cell + Dirs::N : Cell + Dirs::W, OUT Los);
		}

		FIntVector2 sideSE = Cell + Dirs::SE;
		if (IsInGrid(sideSE)
			&& !IsWall(sideSE)
			&& !IsWall(Cell + Dirs::S)
			&& !IsWall(Cell + Dirs::E))
		{
			BresenhamsRay2D(Goal + Dirs::N, GoalToCell.Y > 0 ? Cell + Dirs::E : Cell + Dirs::S, OUT Los);
		}
	}
	else {
		FIntVector2 sideNE = Cell + Dirs::NE;
		if (IsInGrid(sideNE)
			&& !IsWall(sideNE)
			&& !IsWall(Cell + Dirs::N)
			&& !IsWall(Cell + Dirs::E))
		{
			BresenhamsRay2D(Goal + Dirs::S, GoalToCell.Y > 0 ? Cell + Dirs::N : Cell + Dirs::E, OUT Los);
		}

		FIntVector2 sideSW = Cell + Dirs::SW;
		if (IsInGrid(sideSW)
			&& !IsWall(sideSW)
			&& !IsWall(Cell + Dirs::S)
			&& !IsWall(Cell + Dirs::W))
		{
			BresenhamsRay2D(Goal + Dirs::N, GoalToCell.Y > 0 ? Cell + Dirs::W : Cell + Dirs::S, OUT Los);
		}
	}
}

void FCrowdPFModule::Impl::VisitCell(std::deque<FIntVector2>& WaveFront, const FIntVector2& Cell, float CurrentCost, const FIntVector2& Goal, OUT std::deque<FIntVector2>& SecondWaveFront, bool bLosPass) {
	UE_LOG(LogCrowdPF, VeryVerbose, TEXT("VisitCell Processing [%d, %d]"), Cell.X, Cell.Y);

	if (IsInGrid(Cell) == false || IntegrationFields[Cell.Y *  O.Cols + Cell.X].LOS)
	{
		return;
	}

	if (!bLosPass && IsWall(Cell)) // used to be !bLosPass &&
	{
		return;
	}

	if (bLosPass && IsWall(Cell))
	{
		std::deque<FIntVector2> Los;
		GetLos(Cell, Goal, OUT Los);
		for (auto& LosCell : Los)
		{
			int LosCellIdx = ToLinearIdx(LosCell);
			IntegrationFields[LosCellIdx].WaveFrontBlocked = true;
			IntegrationFields[LosCellIdx].LOS = false; // false is default, but let's make sure
		}
		SecondWaveFront.insert(SecondWaveFront.end(), Los.begin(), Los.end());

		return;
	}

	int Idx = ToLinearIdx(Cell);
	float NewCost = CurrentCost + CostFields[Idx];
	float OldCost = IntegrationFields[Idx].IntegratedCost;

	if (NewCost < OldCost * O.SignificantCostReduction) {
		IntegrationFields[Idx].IntegratedCost = NewCost;
		if (IntegrationFields[Idx].WaveFrontBlocked == false)
		{
			WaveFront.push_back(Cell); // calculate WaveFrontBlocked but don't propagate
			IntegrationFields[Idx].LOS = bLosPass;
			UE_LOG(LogCrowdPF, VeryVerbose, TEXT("VisitCell: Pushing [%d, %d]"), Cell.X, Cell.Y);
		}

	}
}

void FCrowdPFModule::Impl::PropagateWave(std::deque<FIntVector2>& WaveFront, bool bLosPass, const FIntVector2& Goal, OUT std::deque<FIntVector2>& SecondWaveFront)
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("STAT_CrowdPF_PropagateWave"), STAT_CrowdPF_PropagateWave, STATGROUP_CrowdPF);
	while (!WaveFront.empty()) {
		FIntVector2 Current = WaveFront.front();
		WaveFront.pop_front();

		float CurrentCost = IntegrationFields[Current.Y *  O.Cols + Current.X].IntegratedCost;

		VisitCell(WaveFront, FIntVector2(Current.X + 1, Current.Y), CurrentCost, Goal, SecondWaveFront, bLosPass);
		VisitCell(WaveFront, FIntVector2(Current.X - 1, Current.Y), CurrentCost, Goal, SecondWaveFront, bLosPass);
		VisitCell(WaveFront, FIntVector2(Current.X, Current.Y + 1), CurrentCost, Goal, SecondWaveFront, bLosPass);
		VisitCell(WaveFront, FIntVector2(Current.X, Current.Y - 1), CurrentCost, Goal, SecondWaveFront, bLosPass);
	}
}
/* End Eikonal*/

void FCrowdPFModule::Impl::ConvertFlowTilesToPath(const FVector& WorldOrigin, const FVector& WorldGoal, FNavPathSharedPtr& OutPath)
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("STAT_CrowdPF_ConvertFlowTilesToPath"), STAT_CrowdPF_ConvertFlowTilesToPath, STATGROUP_CrowdPF);
	FIntVector2 Origin = WorldVectToGridVect(WorldOrigin);
	FIntVector2 Goal = WorldVectToGridVect(WorldGoal);

	TArray<FVector> Points;
	Points.Add(WorldOrigin);

	bool bReachedLOS = false;
	Dirs::EDirection LastDirection = static_cast<Dirs::EDirection>(-1);

	while (!bReachedLOS) {
		int idx = ToLinearIdx(Origin);
		if (idx < 0 || idx >= FlowFields.Num()) {
			break;
		}

		const FlowField& CurrentField = FlowFields[idx];
		if (CurrentField.LOS) {
			FVector CurrentWorldPos = GridVectToWorldVect(Origin);
			Points.Add(CurrentWorldPos);
			bReachedLOS = true;
			break;
		}

		if (LastDirection != CurrentField.Dir) {
			FVector CurrentWorldPos = GridVectToWorldVect(Origin);
			Points.Add(CurrentWorldPos);
			LastDirection = CurrentField.Dir;
		}

		FIntVector2 DirectionOffset = Dirs::DIRS.at(CurrentField.Dir);
		FIntVector2 NextGridPos = Origin + DirectionOffset;

		Origin = NextGridPos;
	}
	Points.Add(WorldGoal);
	OutPath = MakeShared<FNavigationPath, ESPMode::ThreadSafe>(Points);

	OutPath->GetPathPoints()[0].Flags = 81665; // Beginning node
	for (int i = 1; i < OutPath->GetPathPoints().Num() - 1; ++i) {
		OutPath->GetPathPoints()[i].Flags = 81664; // Intermediate nodes
	}
	OutPath->GetPathPoints().Last().Flags = 81666; // End node
}


void FCrowdPFModule::Impl::CalculateFlowFields()
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("STAT_CrowdPF_CalculateFlowFields"), STAT_CrowdPF_CalculateFlowFields, STATGROUP_CrowdPF);
	auto DiagonalReachable = [this](const int CurIdx, const Dirs::EDirection NewDir) {
		return IntegrationFields[ApplyDir(CurIdx, Next(NewDir))].IntegratedCost != FLT_MAX && IntegrationFields[ApplyDir(CurIdx, Prev(NewDir))].IntegratedCost != FLT_MAX; // TODO change to binary comparison?
		};

	for (int i = 0; i < FlowFields.Num(); ++i)
	{
		FlowFields[i].LOS = IntegrationFields[i].LOS;

		if (FlowFields[i].LOS)
		{
			continue;
		}

		float CurrentCost = IntegrationFields[i].IntegratedCost;
		float BestCost = FLT_MAX;
		Dirs::EDirection BestDir = Dirs::EDirection::North; // Begin somewhere
		int BestIdx;

		for (const auto& pair : Dirs::DIRS) {
			Dirs::EDirection NewDir = pair.first;
			int NewIdx = ApplyDir(i, pair.second);

			if (IsValidIdx(NewIdx) && IntegrationFields[NewIdx].IntegratedCost != FLT_MAX) { // TODO change to binary comparison?

				if (Dirs::IsDiagonal(NewDir) && DiagonalReachable(i, NewDir) == false) continue;


				float LosBonus = (IntegrationFields[NewIdx].IntegratedCost - CurrentCost) * IntegrationFields[NewIdx].LOS * 10.f; // Prefer LOS only if contributes to goal
				float NewCost = IntegrationFields[NewIdx].IntegratedCost + LosBonus;
				//if (CurIdx == 62) { __debugbreak(); }
				if (NewCost < BestCost)
				{
					BestIdx = NewIdx;
					BestCost = NewCost;
					BestDir = NewDir;
				}
			}
		}
		FlowFields[i].Dir = BestDir;
		FlowFields[i].Completed = true;
	}
}

void FCrowdPFModule::Impl::CalculateCostFields()
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("STAT_CrowdPF_CalculateCostFields"), STAT_CrowdPF_CalculateCostFields, STATGROUP_CrowdPF);
	CostFields.Init(1,  O.Cols * O.Rows);
	FVector HitLocation;
	FHitResult OutHit;
	for (int y = 0; y < O.Rows; ++y)
	{
		for (int x = 0; x <  O.Cols; ++x)
		{
			FVector Start = O.CostTraceYStart + FVector(toUU(x) + O.CellSize / 2, toUU(y) + O.CellSize / 2, 0.f);
			FVector End = Start + O.CostTraceDirection;

			FCollisionObjectQueryParams ObjectQueryParams(FCollisionObjectQueryParams::AllObjects);
			ObjectQueryParams.RemoveObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
			bool bLineTraceObstructed = pWorld->LineTraceSingleByObjectType(OutHit, Start, End, ObjectQueryParams);

			CostFields[y *  O.Cols + x] = bLineTraceObstructed ? UINT8_MAX : 1;
		}
	}
}

void FCrowdPFModule::Impl::UpdateDirtyCostFields()
{
	/* TODO Implement */
}

bool FCrowdPFModule::Impl::GetNeedToRecalculate(const FIntVector2& Goal)
{
	return bNeedToRecalculate;
}

void FCrowdPFModule::Impl::SetNeedToRecalculate(const bool bValue)
{
	bNeedToRecalculate = bValue;
}

void FCrowdPFModule::Impl::DoFlowTiles(const FVector& WorldOrigin, const FVector& WorldGoal, OUT FNavPathSharedPtr& OutPath)
{
	if (!ensure(pWorld)){ return; }

	FIntVector2 Goal = WorldVectToGridVect(WorldGoal);
	FIntVector2 Origin = WorldVectToGridVect(WorldOrigin);

	if (GetNeedToRecalculate(Goal))
	{
		//Cost Fields
		UpdateDirtyCostFields();

		// Eikonal
		std::deque<FIntVector2> WaveFront;
		WaveFront.push_back(Goal);
		std::deque<FIntVector2> SecondWaveFront;
		std::deque<FIntVector2> DummyWaveFront; // TODO refactor
		IntegrationFields.Init({ FLT_MAX, false, false },  O.Cols * O.Rows);
		IntegrationFields[Goal.Y *  O.Cols + Goal.X].IntegratedCost = 0;
		IntegrationFields[Goal.Y *  O.Cols + Goal.X].LOS = true;
		PropagateWave(WaveFront, /*bLosPass =*/ true, Goal, SecondWaveFront);
		PropagateWave(SecondWaveFront, /*bLosPass =*/ false, Goal, DummyWaveFront); // todo templating

		// Flow Fields
		FlowFields.Init({ Dirs::EDirection(), false, 0 },  O.Cols * O.Rows); // TODO optimize: can we omit constructing these?
		CalculateFlowFields();

		SetNeedToRecalculate(false);

		// Debug
		if (O.bDebugDraw)
		{
			DrawCoords();
			DrawCosts();
			DrawIntegration();
			DrawFlows();
		}
	}

	ConvertFlowTilesToPath(WorldOrigin, WorldGoal, OutPath);
}

void FCrowdPFModule::Impl::Init(UWorld* _World, FCrowdPFOptions _Options)
{
	pWorld = _World;
	O = _Options;
	CalculateCostFields();
}

void FCrowdPFModule::Impl::DrawCosts()
{
	if (!O.bDrawCosts)
	{
		return;
	}
	ensure(pWorld);
	for (int y = 0; y < O.Rows; ++y)
	{
		for (int x = 0; x <  O.Cols; ++x)
		{
			FVector RayStart = O.CostTraceYStart + FVector(toUU(x) + O.CellSize / 2, toUU(y) + O.CellSize / 2, 0.f);
			FVector RayEnd = RayStart + O.CostTraceDirection;
			// UE_LOG(LogCrowdPF, Log, TEXT("CostFields [%d][%d] = [%d]"),i, j, CostFields[i *  O.Cols + j]);
			DrawDebugDirectionalArrow(pWorld, RayStart, RayEnd, 3.0f, CostFields[y *  O.Cols + x] == UINT8_MAX ? FColor::Red : FColor::Green, true, -1.f, 0, 15.f);
		}
	}
}

void FCrowdPFModule::Impl::DrawIntegration()
{
	if (!O.bDrawIntegration)
	{
		return;
	}
	ensure(pWorld);
	FlushPersistentDebugLines(pWorld);

	for (int y = 0; y < O.Rows; ++y)
	{
		for (int x = 0; x <  O.Cols; ++x)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			{
				FVector TextStart = { toUU(x) + O.HCellSize(), toUU(y) + O.HCellSize() , O.TextHeight()}; // Top corner of cell
				auto IntegratedCost = FString::FromInt(IntegrationFields[y *  O.Cols + x].IntegratedCost);
				if (IntegrationFields[y *  O.Cols + x].IntegratedCost == FLT_MAX)
				{
					IntegratedCost = "MAX";
				}

				auto TextActor = pWorld->SpawnActor<ATextRenderActor>(ATextRenderActor::StaticClass(), TextStart, FRotator(90, 0, 180), SpawnParameters);
				TextActor->GetTextRender()->SetText(FText::FromString(IntegratedCost));
				TextActor->GetTextRender()->SetTextRenderColor(FColor::Magenta);
			}

			{
				FVector TextStart = { toUU(x) + O.HCellSize(), toUU(y) + O.QCellSize(), O.TextHeight()}; // Top corner of cell
				FString WaveFrontBlocked = IntegrationFields[y *  O.Cols + x].WaveFrontBlocked ? "|" : "";
				auto TextActor = pWorld->SpawnActor<ATextRenderActor>(ATextRenderActor::StaticClass(), TextStart, FRotator(90, 0, 180), SpawnParameters);
				TextActor->GetTextRender()->SetText(FText::FromString(WaveFrontBlocked));
				TextActor->GetTextRender()->SetTextRenderColor(FColor::Black);
			}

			{
				FVector RayStart = O.CostTraceYStart + FVector(toUU(x) + O.CellSize / 2, toUU(y) + O.CellSize / 2, 0.f);
				FVector RayEnd = RayStart + O.CostTraceDirection;
				// UE_LOG(LogCrowdPF, Log, TEXT("CostFields [%d][%d] = [%d]"),i, j, CostFields[i *  O.Cols + j]);
				FVector Points[]{
					{5.f, 5.f, 0.f},
					{O.CellSize - 5.f, O.CellSize - 5.f, 0.f}
				};
				FBox Box{ Points, 2 };
				FTransform Transform{ FVector(toUU(x), toUU(y), O.LosFlagHeight()) };
				FColor Color = IntegrationFields[y *  O.Cols + x].LOS ? FColor::White : FColor::Blue;
				if (IntegrationFields[y *  O.Cols + x].LOS == false)
				{
					int a = 5;
				}
				else
				{
					int b = 6;
				}
				DrawDebugSolidBox(pWorld, Box, Color, Transform, true);
			}
		}
	}
}

void FCrowdPFModule::Impl::DrawFlows()
{
	if (!O.bDrawFlows)
	{
		return;
	}

	ensure(pWorld);
	FVector Ray{ 0.f, 0.f, O.FlowArrowHeight()};

	for (int y = 0; y < O.Rows; ++y)
	{
		for (int x = 0; x <  O.Cols; ++x)
		{
			if (FlowFields[y *  O.Cols + x].Completed == true)
			{
				Dirs::EDirection Dir = FlowFields[y *  O.Cols + x].Dir;
				FIntVector2 IntOffset = Dirs::DIRS.at(Dir) * 25;
				FVector Offset{ IntOffset.X * 1.f, IntOffset.Y * 1.f, 0.f };
				Ray.Y = y * 100.f + 50;
				Ray.X = x * 100.f + 50;

				FVector Start = Ray - Offset;
				FVector End = Ray + Offset;

				DrawDebugDirectionalArrow(pWorld, Start, End, 3.f, FColor::Green, true, 9999999.f, 0,  O.QCellSize() / 2.f);

				//UE_LOG(LogCrowdPF, Log, TEXT("FlowFields[%d][%d].Dir = [%d]"), y, x, (int)FlowFields[y *  O.Cols + x].Dir);
				//UE_LOG(LogCrowdPF, Log, TEXT("Start = %s"), *Start.ToString());
				//UE_LOG(LogCrowdPF, Log, TEXT("End = %s"), *End.ToString());
			}
		}
	}
}

void FCrowdPFModule::Impl::DrawBox(FIntVector2 At, FColor Color)
{
	ensure(pWorld);
	FVector Center{
		toUU(At.X) + O.HCellSize(),
		toUU(At.Y) + O.HCellSize(),
		60.f
	};
	FVector Extent = FVector( O.QCellSize(),  O.QCellSize(),  O.QCellSize());
	DrawDebugBox(pWorld, Center, Extent, Color, true);
	//UE_LOG(LogCrowdPF, Log, TEXT("Draw Box: Center = %s; Extent = %s"), *Center.ToString(), *Extent.ToString());
}

void FCrowdPFModule::Impl::DrawBox(int At, FColor Color)
{
	return DrawBox(ToFIntVector2(At), Color);
}

void FCrowdPFModule::Impl::DrawCoords()
{
	if (!O.bDrawCoords)
	{
		return;
	}
	ensure(pWorld);
	DrawDebugCoordinateSystem(pWorld, { 0.f, 0.f, 0.f }, FRotator(0.f), O.CellSize, true);

	for (int y = 0; y < O.Rows; ++y)
	{
		for (int x = 0; x <  O.Cols; ++x)
		{
			FVector TextStart = { toUU(x) +  O.QCellSize(), toUU(y), O.TextHeight()}; // Bottom part of cell // TODO why x,y reversed?

			// UE_LOG(LogCrowdPF, Log, TEXT("IntegrationFields [%d][%d] = [%s]"), i, j, *IntegratedCost
			FText Coords = FText::FromString(" [" + FString::FromInt(x) + ", " + FString::FromInt(y) + "]");
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			auto TextActor = pWorld->SpawnActor<ATextRenderActor>(ATextRenderActor::StaticClass(), TextStart, FRotator(90, 0, 180), SpawnParameters);
			TextActor->GetTextRender()->SetText(Coords);
			TextActor->GetTextRender()->SetTextRenderColor(FColor::Turquoise);
		}
	}
}

#define BREAK_IF_EQUAL(current, at) if ((current) == (at)) { __debugbreak(); }

const int FCrowdPFModule::Impl::ApplyDir(const int Idx, const FIntVector2& Dir) {
	int Result = Idx + Dir.Y *  O.Cols + Dir.X;
	return Result;
}

bool FCrowdPFModule::Impl::IsInGrid(int X, int Y)
{
	return X >= 0 && X <  O.Cols && Y >= 0 && Y < O.Rows;
}

bool FCrowdPFModule::Impl::IsInGrid(const FIntVector2& Cell) {
	return IsInGrid(Cell.X, Cell.Y);
}

bool FCrowdPFModule::Impl::IsInGrid(int Idx)
{
	int X = Idx %  O.Cols;
	int Y = Idx /  O.Cols;
	return IsInGrid(X, Y);
}

FIntVector2 FCrowdPFModule::Impl::ToFIntVector2(int LinearIdx)
{
	return FIntVector2(
		LinearIdx %  O.Cols,
		LinearIdx /  O.Cols
	);
}

FIntVector2 FCrowdPFModule::Impl::WorldVectToGridVect(const FVector& Vect)
{
	return FIntVector2(
		Vect.X / O.CellSize,
		Vect.Y / O.CellSize
	);
}

FVector FCrowdPFModule::Impl::GridVectToWorldVect(const FIntVector2& Vect)
{
	return FVector(
		toUU(Vect.X) + O.HCellSize(),
		toUU(Vect.Y) + O.HCellSize(),
		O.PlaneHeight
	);
}


FIntVector2 FCrowdPFModule::Impl::ToFIntVector2(FVector Vect)
{
	return FIntVector2(
		static_cast<int>(Vect.X),
		static_cast<int>(Vect.Y)
	);
}

int FCrowdPFModule::Impl::ToLinearIdx(FIntVector2 IntVector2)
{
	return IntVector2.Y *  O.Cols + IntVector2.X;
}

FVector2D FCrowdPFModule::Impl::ToVector2D(const FIntVector2& IntVector2)
{
	FVector2D Result;
	Result.X = static_cast<float>(IntVector2.X);
	Result.Y = static_cast<float>(IntVector2.Y);
	return Result;
};

bool FCrowdPFModule::Impl::IsValidIdx(int Idx) const
{
	return Idx >= 0 && Idx <  O.Cols * O.Rows;
}

FVector FCrowdPFModule::Impl::addZ(FVector2D Vect, float Z)
{
	return FVector(Vect.X, Vect.Y, Z);
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCrowdPFModule, CrowdPF)