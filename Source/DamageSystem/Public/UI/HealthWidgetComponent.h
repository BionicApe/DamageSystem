// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class DAMAGESYSTEM_API UHealthWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	
	virtual void InitWidget() override;
};
