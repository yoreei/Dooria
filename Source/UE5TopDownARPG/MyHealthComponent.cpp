//#include "MyHealthComponent.h"
//#include "Components/WidgetComponent.h"
//
//UMyHealthComponent::UMyHealthComponent()
//{
//    // Set default values for this component's properties
//    MaxHealth = 100.f;
//    CurrentHealth = MaxHealth;
//
//    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
//    WidgetComponent->SetCastShadow(false);
//    WidgetComponent->SetReceivesDecals(false);
//    WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//    WidgetComponent->SetupAttachment(RootComponent);
//
//    // Activate ticking in order to update the cursor every frame.
//    PrimaryActorTick.bCanEverTick = true;
//    PrimaryActorTick.bStartWithTickEnabled = true;
//
//    OnTakeAnyDamage.AddDynamic(this, &UMyHealthComponent::TakeAnyDamage);
//}
//
//void UMyHealthComponent::PostInitProperties()
//{
//    Super::PostInitProperties();
//    if (IsValid(WidgetComponent->GetWidgetClass()))
//    {
//        WidgetComponent->InitWidget();
//        HealthbarWidget = Cast<UHealthbarWidget>(WidgetComponent->GetUserWidgetObject());
//    }
//}
//
//void UMyHealthComponent::BeginPlay()
//{
//    Super::BeginPlay();
//    // Initialize component
//
//    if (IsValid(HealthbarWidget))
//    {
//        float HealthPercent = Health / MaxHealth;
//        HealthbarWidget->SetPercent(HealthPercent);
//    }
//}
//
//void UMyHealthComponent::TakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser)
//{
//	Health -= Damage;
//	OnRep_SetHealth(Health + Damage);
//	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Health %f"), Health);
//	if (IsValid(HealthbarWidget))
//	{
//		float HealthPercent = Health / MaxHealth;
//		HealthbarWidget->SetPercent(HealthPercent);
//	}
//	if (Health <= 0.0f)
//	{
//		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
//		if (TimerManager.IsTimerActive(DeathHandle) == false)
//		{
//			GetWorld()->GetTimerManager().SetTimer(DeathHandle, this, &AUE5TopDownARPGCharacter::Death, DeathDelay);
//		}
//	}
//}
//
//void UMyHealthComponent::OnRep_SetHealth(float OldHealth)
//{
//	if (GEngine)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Health %f"), Health));
//	}
//}
//
//void UMyHealthComponent::Death()
//{
//	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Death"));
//	AUE5TopDownARPGGameMode* GameMode = Cast<AUE5TopDownARPGGameMode>(GetWorld()->GetAuthGameMode());
//	if (IsValid(GameMode))
//	{
//		GameMode->EndGame(false);
//	}
//
//	FActorSpawnParameters SpawnParameters;
//	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//
//	FVector Location = GetActorLocation();
//	FRotator Rotation = GetActorRotation();
//	if (FMath::RandBool())
//	{
//		AActor* SpawnedActor = GetWorld()->SpawnActor(AfterDeathSpawnClass, &Location, &Rotation, SpawnParameters);
//	}
//
//	GetWorld()->GetTimerManager().ClearTimer(DeathHandle);
//	AUE5TopDownARPGPlayerController* PlayerController = Cast<AUE5TopDownARPGPlayerController>(GetController());
//	if (IsValid(PlayerController))
//	{
//		PlayerController->OnPlayerDied();
//	}
//	Destroy();
//}
