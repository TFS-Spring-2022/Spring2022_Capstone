// Created by Spring2022_Capstone team


#include "DamageNumberWidget.h"
#include "Components/TextBlock.h"
#include "Spring2022_Capstone/Spring2022_Capstone.h"

void UDamageNumberWidget::SetDamageText(const FText& Text)
{
	if (DamageTextBlock)
	{
		DamageTextBlock->SetText(Text);
	}
}

void UDamageNumberWidget::SetColorBySurfaceType(EPhysicalSurface SurfaceType)
{
	if (DamageTextBlock)
	{
		FLinearColor Color;
		switch (SurfaceType)
		{
		case SURFACE_FleshDefault:
			Color = FLinearColor::Red;
			break;
		case SURFACE_FleshVulnerable:
			Color = FLinearColor::Yellow;
			break;
		default:
			Color = FLinearColor::Blue;
			break;
		}
		DamageTextBlock->SetColorAndOpacity(Color);
	}
}

void UDamageNumberWidget::Despawn()
{
	RemoveFromParent();
}
