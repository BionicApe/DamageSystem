
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
	AActor* Victim = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	UHealthComponent* VictimHealth = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AController* VictimController = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AActor* Killer = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AController* KillerController = nullptr;

};

USTRUCT(BlueprintType, Blueprintable)
struct FTakeDamageProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	float DamageTaken;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AActor* Victim = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	UHealthComponent* VictimHealth = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AController* VictimController = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AActor* Killer = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, Category = DamageSystem)
	AController* KillerController = nullptr;

};