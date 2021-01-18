// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageSystemTypes.h"
#include "HealthWidget.generated.h"

class UHealthComponent;
class UImage;

/**
 *
 */
UCLASS()
class DAMAGESYSTEM_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInterface* MasterMaterial;

	UPROPERTY(Transient, DuplicateTransient)
	UMaterialInstanceDynamic* MID;

	UPROPERTY(meta = (BindWidget))
	UImage* HealthBarImage;

	UPROPERTY(Transient)
	UHealthComponent* HealthComp;

public:

	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetupHealthComponent(UHealthComponent* NewHealthComp);

	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
	void OnDie(FActorKilled ActorKilledProperties);
	void OnDie_Implementation(FActorKilled ActorKilledProperties);

	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
	void OnTakeDamage(FTakeDamageProperties TakeDamageProperties);
	void OnTakeDamage_Implementation(FTakeDamageProperties TakeDamageProperties);

	UFUNCTION()
	void OnHealthChanged(int32 OldHealth, int32 NewHealth);

	void SetHealthPercentage(float Percentage);
};