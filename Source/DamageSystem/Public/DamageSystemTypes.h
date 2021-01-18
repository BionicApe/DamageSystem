
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DamageSystemTypes.generated.h"

class AActor;
class UHealthComponent;
class AController;

USTRUCT(BlueprintType, Blueprintable)
struct FActorKilled
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	float DamageTaken;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AActor* Victim;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	UHealthComponent* VictimHealth;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AController* VictimController;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AActor* Killer;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AController* KillerController;

};

USTRUCT(BlueprintType, Blueprintable)
struct FTakeDamageProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	float DamageTaken;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AActor* Victim;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	UHealthComponent* VictimHealth;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AController* VictimController;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AActor* Killer;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AController* KillerController;

};