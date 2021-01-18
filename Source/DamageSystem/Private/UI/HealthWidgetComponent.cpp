// Created by Bionic Ape. All Rights Reserved.


#include "UI/HealthWidgetComponent.h"
#include "GameFramework/Actor.h"
#include "UI/HealthWidget.h"
#include "Components/HealthComponent.h"

void UHealthWidgetComponent::InitWidget()
{
	Super::InitWidget();

	if (UHealthWidget* HealthWidget = Cast<UHealthWidget>(GetWidget()))
	{
		if (UHealthComponent* HealthComp = Cast<UHealthComponent>(GetOwner()->GetComponentByClass(UHealthComponent::StaticClass())))
		{
			HealthWidget->SetupHealthComponent(HealthComp);
		}
	}
}
