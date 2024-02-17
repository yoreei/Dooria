// Fill out your copyright notice in the Description page of Project Settings.

#include "ACrowdPFAIController.h"
#include "NavigationData.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "CrowdPF/Public/CrowdPF.h"
#include "UE5TopDownARPGGameMode.h"
#include "UE5TopDownARPG.h"
#include "Env/Door.h"
#include "Logging/StructuredLog.h"

ACrowdPFAIController::ACrowdPFAIController()
{
}

void ACrowdPFAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

void ACrowdPFAIController::BeginPlay()
{
    Super::BeginPlay();
}

/*
    * Profiling procedure
    * In console, write:
    trace.enable counters,cpu,stats
    stat NamedEvents
    trace.start
    <run benchmark>
    trace.stop
*/

void ACrowdPFAIController::FindPathForMoveRequest(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query, FNavPathSharedPtr& OutPath) const
{
    UE_LOGFMT(LogUE5TopDownARPG, Log, "ACrowdPFAIController received MoveRequest for Door: {0}", *MoveRequest.GetGoalActor()->GetActorNameOrLabel());
    DECLARE_SCOPE_CYCLE_COUNTER(TEXT("STAT_CrowdPF_FindPathForMoveRequest"), STAT_CrowdPF_FindPathForMoveRequest, STATGROUP_CrowdPF);

    AUE5TopDownARPGGameMode* GameMode = Cast<AUE5TopDownARPGGameMode>(GetWorld()->GetAuthGameMode());
    if (!ensure(GameMode)) { return; }

    if(!GameMode->UseCrowdPf)
    {
        Super::FindPathForMoveRequest(MoveRequest, Query, OutPath);
    }
    else
    {
        FCrowdPFModule* CrowdPFModule = FModuleManager::LoadModulePtr<FCrowdPFModule>("CrowdPF");
        if (!ensure(GameMode)) { return; }

        CrowdPFModule->DoFlowTiles(GetPawn()->GetActorLocation(), MoveRequest.GetGoalActor()->GetActorLocation(), OutPath);
    }

    if (!GameMode->DrawDebugPath)
    {
        return;
    }

    UWorld* pWorld = GetWorld();
    ensure(pWorld);
    const TArray<FNavPathPoint>& PathPoints = OutPath->GetPathPoints();
    for (const FNavPathPoint& Point : PathPoints)
    {
        Chaos::TVector<double, 3> Loc = Point.Location;
        FVector loc2 = Point.Location;
        DrawDebugBox(pWorld, loc2, {20.f, 20.f, 20.f}, FColor::Black, true, -1.f, 0, 5.f);
    }
}
