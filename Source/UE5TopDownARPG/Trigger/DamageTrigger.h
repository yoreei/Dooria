// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTrigger.h"
#include "DamageTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API ADamageTrigger : public ABaseTrigger
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dooria")
	bool CanDealDamage = false;

	UFUNCTION(BlueprintNativeEvent, Category = "Dooria")
	void TrapTrigger();
	virtual void TrapTrigger_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Dooria")
	void TrapUntrigger();
	virtual void TrapUntrigger_Implementation();

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float DamageTickRate = 1.0f;

protected:
	virtual void ActionStart(AActor* ActorInRange) override;
	virtual void ActionEnd(AActor* ActorInRange) override;

	void DamageTick();

	UPROPERTY()
	AActor* Target;

	FTimerHandle CustomDamageTickTimerHandle;
};
