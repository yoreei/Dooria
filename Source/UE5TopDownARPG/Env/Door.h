// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Trigger/BaseTrigger.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API ADoorTrigger : public ABaseTrigger
{
	GENERATED_BODY()

protected:
	virtual void ActionStart(AActor* ActorInRange) override;
	
};
