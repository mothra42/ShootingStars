// Fill out your copyright notice in the Description page of Project Settings.


#include "MeteorField.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/StaticMesh.h"
#include "Meteor.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMeteorField::AMeteorField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetupAttachment(RootComponent);

	Field = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Field"));
	Field->SetupAttachment(Root);
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

	SpawnMeteor();
}

void AMeteorField::SpawnMeteor()
{
	UE_LOG(LogTemp, Warning, TEXT("Number of things"));
	if (SpawnPoints.Num() > 0 && Meteor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("WHAT"));
		int32 RandIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		USceneComponent* SpawnPoint = SpawnPoints[RandIndex];
		auto SpawnedActor = GetWorld()->SpawnActor<AActor>(Meteor);
		SpawnedActor->SetActorRelativeLocation(SpawnPoint->GetComponentLocation());
	}
}