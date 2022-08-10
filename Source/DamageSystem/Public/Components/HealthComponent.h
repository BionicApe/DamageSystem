// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageSystemTypes.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDieDelegate, FActorKilled, ActorKilledProperties);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamageDelegate, const FTakeDamageProperties, TakeDamageProperties);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, int32, OldHealth, int32, NewHealth);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAMAGESYSTEM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	static const float POISON_TIME_RECOVERY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, ReplicatedUsing=OnRep_Health)
	float Health = 100.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	float HealthCache = Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, Replicated)
	float MaxHealth = 100.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	bool bIsGodMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	bool bIsPoisoned = false;

	FTimerHandle PoisonTimerHandle;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDieDelegate OnDieEvent;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnTakeDamageDelegate OnTakeDamageEvent;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_Health();

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual float Heal(float HealAmount);

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual float TakeDamageNoInstigator(float Damage, struct FDamageEvent const& DamageEvent, class AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual float OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual float TakeDamageType(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	virtual void Die(float Damage, const class UDamageType* DamageType, class AController* EventInstigator, class AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual bool IsDead() const { return !IsAlive(); }

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual bool IsAlive() const { return Health > 0.0F || bIsGodMode; }

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual void InstantKill(class AController* EventInstigator, class AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual bool IsPoisoned() const { return bIsPoisoned; }

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual void CurePoison() { bIsPoisoned = false; }

	UFUNCTION(BlueprintCallable, Category=Health)
	virtual float GetPercentage() const { return Health / MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual void ApplyMaxHealth() { Health = MaxHealth; }

};
