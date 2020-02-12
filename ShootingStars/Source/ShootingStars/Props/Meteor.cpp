// Fill out your copyright notice in the Description page of Project Settings.


#include "Meteor.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMeteor::AMeteor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 6000.f;
	ProjectileMovement->bShouldBounce = true;
}

// Called when the game starts or when spawned
void AMeteor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

