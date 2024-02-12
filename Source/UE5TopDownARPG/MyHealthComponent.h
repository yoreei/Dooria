//#pragma once
//
//#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
//#include "MyHealthComponent.generated.h"
//
//UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
//class UE5TOPDOWNARPG_API UMyHealthComponent : public UActorComponent
//{
//    GENERATED_BODY()
//
//public:
//    UMyHealthComponent();
//
//protected:
//    virtual void BeginPlay() override;
//
//public:
//    FORCEINLINE float GetHealth()const { return CurrentHealth; }
//
//    // Health-related properties
//    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
//    float MaxHealth;
//
//    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
//    float CurrentHealth;
//
//    // Other health-related methods...
//private:
//    UPROPERTY(EditDefaultsOnly)
//    class UWidgetComponent* WidgetComponent;
//
//    UPROPERTY()
//    class UHealthbarWidget* HealthbarWidget;
//
//    UPROPERTY(EditDefaultsOnly)
//    float DeathDelay = 1.0f;
//
//    FTimerHandle DeathHandle;
//
//    UPROPERTY(EditDefaultsOnly)
//    TSubclassOf<AActor> AfterDeathSpawnClass;
//
//    UFUNCTION()
//    void TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigateBy, AActor* DamageCauser);
//
//    UFUNCTION()
//    void OnRep_SetHealth(float OldHealth);
//
//    void Death();
//
//    virtual void PostInitProperties() override;
//};
