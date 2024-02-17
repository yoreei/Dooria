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

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Dooria")
	void CustomHover();
	virtual void CustomHover_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Dooria")
	void CustomUnhover();
	virtual void CustomUnhover_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Dooria")
	void CustomClick();
	virtual void CustomClick_Implementation();

protected:
	virtual void ActionStart(AActor* ActorInRange) override;
};
