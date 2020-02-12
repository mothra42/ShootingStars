// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShootingStarsHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGSTARS_API AShootingStarsHUD : public AHUD
{
	GENERATED_BODY()

public:
	AShootingStarsHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	FVector2D GetCrosshairDrawPosition();

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	FVector2D CrosshairDrawPosition;
};
