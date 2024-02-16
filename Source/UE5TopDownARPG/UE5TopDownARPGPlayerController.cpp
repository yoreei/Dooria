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
#include "UE5TopDownARPG.h"

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
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AUE5TopDownARPGPlayerController::OnInputStarted);
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AUE5TopDownARPGPlayerController::OnSetDestinationReleased);
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AUE5TopDownARPGPlayerController::OnSetDestinationReleased);

		EnhancedInputComponent->BindAction(ActivateShowPathsAction, ETriggerEvent::Started, this, &AUE5TopDownARPGPlayerController::onActivateShowPathsAction);
		EnhancedInputComponent->BindAction(ActivateDestroyWallAction, ETriggerEvent::Started, this, &AUE5TopDownARPGPlayerController::onActivateDestroyWallAction);
		EnhancedInputComponent->BindAction(ActivateFreeRoamAction, ETriggerEvent::Started, this, &AUE5TopDownARPGPlayerController::onActivateFreeRoamAction);

		// Setup touch input events
		// TODO clean?
		//EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AUE5TopDownARPGPlayerController::OnInputStarted);
		//EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AUE5TopDownARPGPlayerController::OnTouchTriggered);
		//EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AUE5TopDownARPGPlayerController::OnTouchReleased);
		//EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AUE5TopDownARPGPlayerController::OnTouchReleased);
	}
}

// TODO clean?
//void AUE5TopDownARPGPlayerController::OnInputStarted()
//{
//	StopMovement();
//}

// Triggered every frame when the input is held down
void AUE5TopDownARPGPlayerController::OnSetDestinationTriggered()
{
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

// TODO clean?
//void AUE5TopDownARPGPlayerController::OnSetDestinationReleased()
//{
//	// If it was a short press
//	if (FollowTime <= ShortPressThreshold)
//	{
//		// We move there and spawn some particles
//		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
//		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
//	}
//
//	FollowTime = 0.f;
//}

// TODO clean?
//void AUE5TopDownARPGPlayerController::OnTouchTriggered()
//{
//	bIsTouch = true;
//	OnSetDestinationTriggered();
//}
//
//void AUE5TopDownARPGPlayerController::OnTouchReleased()
//{
//	bIsTouch = false;
//	OnSetDestinationReleased();
//}


	// TODO move to other function
	//AUE5TopDownARPGCharacter* ARPGCharacter = Cast<AUE5TopDownARPGCharacter>(GetPawn());
	//if (IsValid(ARPGCharacter))
	//{
	//	FHitResult Hit;
	//	bool bHitSuccessful = false;
	//	if (bIsTouch)
	//	{
	//		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	//	}
	//	else
	//	{
	//		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	//	}

	//	// If we hit a surface, cache the location
	//	if (bHitSuccessful)
	//	{
	//		ARPGCharacter->ActivateAbility(Hit.Location);
	//	}
	//}

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

		if (Actor)
		{
			UE_LOGFMT(LogUE5TopDownARPG, Log, "Hovered Actor: {0} of type {1} is door: {2}", *Actor->GetActorNameOrLabel(), *Actor->GetClass()->GetName(), IsValid(HoveredDoor));
		}

		if (HoveredDoor != CachedHoveredDoor && IsValid(HoveredDoor))
		{
			UE_LOG(LogUE5TopDownARPG, Log, TEXT("Hovered Door: %s"), HoveredDoor);
		}
		else if (HoveredDoor != CachedHoveredDoor && !IsValid(HoveredDoor))
		{
			UE_LOG(LogUE5TopDownARPG, Log, TEXT("HoveredActor (%s) ! = CachedHoveredDoor (%s) "), HoveredDoor, CachedHoveredDoor);
		}
		CachedHoveredDoor = HoveredDoor;
	}
}