// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingStarsGameMode.h"
#include "UObject/ConstructorHelpers.h"

AShootingStarsGameMode::AShootingStarsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Content/Player/Behavior/BP_PlayerCharacter.uasset"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}