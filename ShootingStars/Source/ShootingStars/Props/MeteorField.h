// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeteorField.generated.h"

UCLASS()
class SHOOTINGSTARS_API AMeteorField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeteorField();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnMeteor();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Field;

	UPROPERTY(EditDefaultsOnly, Category = Spawn)
	TSubclassOf<class AMeteor> Meteor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess = "true"))
	TArray<USceneComponent*> SpawnPoints;
};
