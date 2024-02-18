// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Materials/MaterialInterface.h"
#include "Env/Door.h"
#include "CrowdPF/Public/CrowdPF.h"
#include "UE5TopDownARPGPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class AUE5TopDownARPGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AUE5TopDownARPGPlayerController();

	void OnPlayerDied();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dooria", meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dooria", meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationTouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dooria", meta=(AllowPrivateAccess = "true"))
	class UInputAction* ActivateShowPathsAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dooria", meta = (AllowPrivateAccess = "true"))
	class UInputAction* ActivateDestroyWallAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dooria", meta = (AllowPrivateAccess = "true"))
	class UInputAction* ActivateFreeRoamAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dooria", meta = (AllowPrivateAccess = "true"))
	class UInputAction* ActivateCheat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dooria")
	UMaterialInterface* OutlineMaterial;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnSetDestinationTriggered();
	// TODO clean?
	/*void OnInputStarted();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();*/

	// Player Abilities
	void onActivateFreeRoamAction();
	void onActivateShowPathsAction();
	void onActivateDestroyWallAction();
	void onActivateCheat();

	bool CanFreeRoam = false;

private:
	FVector CachedDestination;
	ADoorTrigger* CachedHoveredDoor;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed

	void Tick(float DeltaTime) override;
};


