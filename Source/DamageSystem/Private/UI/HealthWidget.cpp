// Created by Bionic Ape. All Rights Reserved.


#include "UI/HealthWidget.h"
#include "Components/HealthComponent.h"
#include "Components/Image.h"

bool UHealthWidget::Initialize()
{
	if (Super::Initialize())
	{
		MID = UMaterialInstanceDynamic::Create(MasterMaterial, this);
		HealthBarImage->SetBrushFromMaterial(MID);
		return true;
	}
	return false;
}

void UHealthWidget::SetupHealthComponent(UHealthComponent* NewHealthComp)
{
	HealthComp = NewHealthComp;

	if (HealthComp)
	{
		HealthComp->OnDieEvent.AddDynamic(this, &UHealthWidget::OnDie);
		HealthComp->OnHealthChanged.AddDynamic(this, &UHealthWidget::OnHealthChanged);
		SetHealthPercentage(HealthComp->GetPercentage());
	}
}

void UHealthWidget::OnDie_Implementation(FActorKilled ActorKilledProperties)
{
	SetHealthPercentage(0.f);
}

void UHealthWidget::OnTakeDamage_Implementation(FTakeDamageProperties TakeDamageProperties)
{
	SetHealthPercentage(TakeDamageProperties.VictimHealth->GetPercentage());
}

void UHealthWidget::OnHealthChanged(int32 OldHealth, int32 NewHealth)
{
	if (HealthComp)
	{
		SetHealthPercentage(HealthComp->GetPercentage());
	}
}

void UHealthWidget::SetHealthPercentage(float Percentage)
{
	MID->SetScalarParameterValue(TEXT("Progress"), Percentage);
}
