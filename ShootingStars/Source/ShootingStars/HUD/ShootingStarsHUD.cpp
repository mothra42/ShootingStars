// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingStarsHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

AShootingStarsHUD::AShootingStarsHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/HUD/Textures/Crosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}


void AShootingStarsHUD::DrawHUD()
{
	Super::DrawHUD();

	const FVector2D Center(Canvas->ClipX * 0.6f, Canvas->ClipY * 0.35f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	CrosshairDrawPosition = FVector2D(Center.X, (Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

FVector2D AShootingStarsHUD::GetCrosshairDrawPosition()
{
	return CrosshairDrawPosition;
}

