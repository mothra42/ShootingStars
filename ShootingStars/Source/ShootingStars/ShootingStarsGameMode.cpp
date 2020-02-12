// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingStarsGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "HUD/ShootingStarsHUD.h"

AShootingStarsGameMode::AShootingStarsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Behavior/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = AShootingStarsHUD::StaticClass();
}