// Fill out your copyright notice in the Description page of Project Settings.


#include "MeteorField.h"
#include "GameFramework/Volume.h"

// Sets default values
AMeteorField::AMeteorField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Field = CreateDefaultSubobject<AVolume>(TEXT("Field"));
	//Field->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMeteorField::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeteorField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

