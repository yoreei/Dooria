// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"
#include "../DooriaGameInstance.h"
#include "../UE5TopDownARPG.h"
#include "../UE5TopDownARPGCharacter.h"
#include "../UE5TopDownARPGGameMode.h"
//#include "../UE5TopDownARPGGameMode.h"

void ADoorTrigger::CustomClick_Implementation()
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("You should override this function, Nil!"));
	ensure(false);
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

void ADoorTrigger::ActionStart(AActor* ActorInRange)
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("You Entered Door..."));
	UDooriaGameInstance* DooriaGameInstance = Cast<UDooriaGameInstance>(GetWorld()->GetGameInstance());
	if (DooriaGameInstance)
	{
		DooriaGameInstance->AdvanceLevel();
	}
}

void ADoorTrigger::BeginPlay()
{
	UObject* Obj = GetDefaultSubobjectByName(TEXT("Door_Collider"));
	UBoxComponent* Box = Cast< UBoxComponent>(Obj);
	if (IsValid(Box))
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("we have box"));
		Box->OnComponentBeginOverlap.AddDynamic(this, &ADoorTrigger::OnOverlapBegin);
		Box->OnComponentEndOverlap.AddDynamic(this, &ADoorTrigger::OnOverlapEnd);
	}
	else {
		ensureAlwaysMsgf(false, TEXT("no box"));
	}
}

void ADoorTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Handle overlap begin event
	AUE5TopDownARPGCharacter* Character = Cast<AUE5TopDownARPGCharacter>(OtherActor);
	if (IsValid(Character))
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("Go to next level"), *OtherActor->GetName());
		UDooriaGameInstance* DooriaGameInstance = Cast<UDooriaGameInstance>(GetWorld()->GetGameInstance());
		if (DooriaGameInstance)
		{
			DooriaGameInstance->AdvanceLevel();
		}
	}
}

void ADoorTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Handle overlap end event
	//UE_LOG(LogUE5TopDownARPG, Log, TEXT("Overlap ended with %s"), *OtherActor->GetName());
}
