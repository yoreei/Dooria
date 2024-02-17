// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Env/Door.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "UE5TopDownARPGCharacter.h"
#include "UE5TopDownARPGHUD.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "Logging/StructuredLog.h"
#include "EnhancedInputSubsystems.h"
#include "CrowdPF/Public/CrowdPF.h"
#include "ACrowdPFAIController.h"
#include "UE5TopDownARPG.h"
#include <Kismet/GameplayStatics.h>

AUE5TopDownARPGPlayerController::AUE5TopDownARPGPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AUE5TopDownARPGPlayerController::OnPlayerDied()
{
	AUE5TopDownARPGHUD* HUD = Cast<AUE5TopDownARPGHUD>(GetHUD());
	if (IsValid(HUD))
	{
		HUD->ShowEndGameScreen();
	}
}

void AUE5TopDownARPGPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AUE5TopDownARPGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AUE5TopDownARPGPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(ActivateShowPathsAction, ETriggerEvent::Started, this, &AUE5TopDownARPGPlayerController::onActivateShowPathsAction);
		EnhancedInputComponent->BindAction(ActivateDestroyWallAction, ETriggerEvent::Started, this, &AUE5TopDownARPGPlayerController::onActivateDestroyWallAction);
		EnhancedInputComponent->BindAction(ActivateFreeRoamAction, ETriggerEvent::Started, this, &AUE5TopDownARPGPlayerController::onActivateFreeRoamAction);
	}
}

// Triggered every frame when the input is held down
void AUE5TopDownARPGPlayerController::OnSetDestinationTriggered()
{
	if (CachedHoveredDoor == nullptr) { return; }
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACrowdPFAIController::StaticClass());
	ACrowdPFAIController* AIController = Cast<ACrowdPFAIController>(FoundActor);
	if (IsValid(AIController))
	{
		UE_LOGFMT(LogUE5TopDownARPG, Log, "SetDestination Door: {0}", *CachedHoveredDoor->GetActorNameOrLabel());
		EPathFollowingRequestResult::Type Result = AIController->MoveToActor(CachedHoveredDoor, 100.f, false, /*bUsePathFinding*/ true, false, NULL, /* bAllowPartialPaths */ true);

		CachedHoveredDoor->CustomClick();
	}
}

void AUE5TopDownARPGPlayerController::onActivateShowPathsAction()
{
	FCrowdPFModule* CrowdPFModule = FModuleManager::LoadModulePtr<FCrowdPFModule>("CrowdPF");
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("onActivateShowPathsAction"));
	//CrowdPFModule->DoFlowTiles(GetPawn()->GetActorLocation(), MoveRequest.GetGoalActor()->GetActorLocation(), OutPath);
}

void AUE5TopDownARPGPlayerController::onActivateDestroyWallAction()
{
	FCrowdPFModule* CrowdPFModule = FModuleManager::LoadModulePtr<FCrowdPFModule>("CrowdPF");
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("onActivateDestroyWallAction"));
	//CrowdPFModule->DoFlowTiles(GetPawn()->GetActorLocation(), MoveRequest.GetGoalActor()->GetActorLocation(), OutPath);
}

void AUE5TopDownARPGPlayerController::onActivateFreeRoamAction()
{
	CanFreeRoam = true;
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("onActivateFreeRoamAction"));
	// TODO set timer
}

void AUE5TopDownARPGPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	if (bHitSuccessful)
	{
		AActor* Actor = HitResult.GetActor();

		ADoorTrigger* HoveredDoor = Cast<ADoorTrigger>(Actor);

		if (IsValid(HoveredDoor) && HoveredDoor != CachedHoveredDoor)
		{
			HoveredDoor->CustomHover();
			UE_LOG(LogUE5TopDownARPG, Log, TEXT("Hovered Door: %s"), HoveredDoor);
			if (IsValid(CachedHoveredDoor))
			{
				CachedHoveredDoor->CustomUnhover();
				UE_LOG(LogUE5TopDownARPG, Log, TEXT("Unhovered Door: %s"), CachedHoveredDoor);
			}

		}
		else if (!IsValid(HoveredDoor) && HoveredDoor != CachedHoveredDoor)
		{
			if (IsValid(CachedHoveredDoor))
			{
				CachedHoveredDoor->CustomUnhover();
				UE_LOG(LogUE5TopDownARPG, Log, TEXT("Unhovered Door: %s"), CachedHoveredDoor);
			}
		}
		CachedHoveredDoor = HoveredDoor;
	}
}