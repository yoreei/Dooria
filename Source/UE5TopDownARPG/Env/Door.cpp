// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "../DooriaGameInstance.h"
#include "../UE5TopDownARPG.h"
#include "../UE5TopDownARPGGameMode.h"
//#include "../UE5TopDownARPGGameMode.h"

void ADoorTrigger::CustomClick_Implementation()
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("You should override this function, Nil!"));
	ensure(false);
}

void ADoorTrigger::ActionStart(AActor* ActorInRange)
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("You Entered Door..."));
	UDooriaGameInstance* DooriaGameInstance = Cast<UDooriaGameInstance>(GetWorld()->GetGameInstance());
	if (DooriaGameInstance)
	{
		DooriaGameInstance->AdvanceLevel();
	}
}

void ADoorTrigger::CustomHover_Implementation()
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("You should override this function, Nil!"));
	ensure(false);
}

void ADoorTrigger::CustomUnhover_Implementation()
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("You should override this function, Nil!"));
	ensure(false);
}
