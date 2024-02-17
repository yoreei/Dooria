// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "../UE5TopDownARPG.h"
//#include "../UE5TopDownARPGGameMode.h"

void ADoorTrigger::CustomClick_Implementation()
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("You should override this function, Nil!"));
	ensure(false);
}

void ADoorTrigger::ActionStart(AActor* ActorInRange)
{
  //AUE5TopDownARPGGameMode* GameMode = Cast<AUE5TopDownARPGGameMode>(GetWorld()->GetAuthGameMode());
  //if (IsValid(GameMode))
  //{
  //  GameMode->EndGame(true);
  //}
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("You Entered Door..."));
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
