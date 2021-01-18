// Created by Javier Sevilla. All rights reseved.

#include "Components/HealthComponent.h"
#include "GameFramework/DamageType.h"
#include "TimerManager.h"
#include "GameFramework/Pawn.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

const float UHealthComponent::POISON_TIME_RECOVERY = 2.f;

static int32 DebugDrawingHealth = 0;
FAutoConsoleVariableRef ConVarDebugHealth(TEXT("dis.debug-health"), DebugDrawingHealth, TEXT("Debug values related to Health System"), ECVF_Cheat);


void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHealthComponent, Health);
	DOREPLIFETIME(UHealthComponent, MaxHealth);
}


void UHealthComponent::OnRep_Health()
{
	if (Health != HealthCache)
	{
		if (Health <= 0)
		{
			FActorKilled ActorKilled;
			ActorKilled.DamageTaken = HealthCache - Health;
			ActorKilled.Victim = GetOwner();
			ActorKilled.VictimHealth = this;
			OnDieEvent.Broadcast(ActorKilled);
		}
		else
		{
			OnHealthChanged.Broadcast(HealthCache,Health);
		}
		HealthCache = Health;
	}	
}

float UHealthComponent::Heal(float HealAmount)
{
	float OldHealth = Health;
	Health = FMath::Clamp(Health + HealAmount, Health, MaxHealth);
	return Health - OldHealth;// We return the Healed amount
}

float UHealthComponent::TakeDamageNoInstigator(float Damage, struct FDamageEvent const& DamageEvent, class AActor* DamageCauser)
{
	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();

	return TakeDamageType(Damage, DamageType, DamageCauser ? DamageCauser->GetInstigatorController() : nullptr, DamageCauser);
}

float UHealthComponent::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();

	return TakeDamageType(Damage, DamageType, EventInstigator, DamageCauser);
}

float UHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	return TakeDamageType(Damage, DamageType, InstigatedBy, DamageCauser);
}

float UHealthComponent::TakeDamageType(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (!bIsGodMode && Damage > 0.f && IsAlive())
	{
		FTakeDamageProperties TakeDamageProperties;
		TakeDamageProperties.Killer = DamageCauser;
		TakeDamageProperties.KillerController = InstigatedBy;
		TakeDamageProperties.VictimHealth = this;

		Health -= Damage;

		if (DamageType->bCausedByWorld)
		{
			bIsPoisoned = true;
			GetOwner()->GetWorldTimerManager().SetTimer(PoisonTimerHandle, this, &UHealthComponent::CurePoison, POISON_TIME_RECOVERY); //Loop each n seconds	
		}

		OnTakeDamageEvent.Broadcast(TakeDamageProperties);

		if (IsDead())
		{
			Die(Damage, DamageType, InstigatedBy, DamageCauser);//executed only once
		}
	}

	//Some debug if requested
	if (DebugDrawingHealth > 0)
	{
		const FString HealthMsg = FString::Printf(TEXT("Damage: %f, Current Health: %f"), Damage, Health);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, HealthMsg);
	}

	return Damage;
}

void UHealthComponent::Die(float Damage, const class UDamageType* DamageType, class AController* EventInstigator, class AActor* DamageCauser)
{
	//Create FActorKilled
	FActorKilled ActorKilled;
	ActorKilled.Killer = DamageCauser;
	ActorKilled.KillerController = EventInstigator;
	ActorKilled.VictimHealth = this;
	if (AActor* Owner = Cast<AActor>(GetOwner()))
	{
		ActorKilled.Victim = Owner;
		if (APawn* Pawn = Cast<APawn>(Owner))
		{
			ActorKilled.VictimController = Pawn->GetController();
		}
	}

	OnDieEvent.Broadcast(ActorKilled);
}

void UHealthComponent::InstantKill(class AController* EventInstigator, class AActor* DamageCauser)
{
	FDamageEvent DamageEvent;
	TakeDamage(Health, DamageEvent, EventInstigator, DamageCauser);
}