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
	void BeginPlay() override;
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

public:
	// Function to handle the event when an overlap begins
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function to handle the event when an overlap ends
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:
	virtual void ActionStart(AActor* ActorInRange) override;
};
