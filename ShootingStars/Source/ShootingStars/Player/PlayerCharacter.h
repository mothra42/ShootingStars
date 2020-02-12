// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SHOOTINGSTARS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	class USpringArmComponent* GetCameraBoom() const;

	class UCameraComponent* GetCameraComponent() const;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* TelekinesisHoldPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess = "true"))
	class APlayerController* PlayerController;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float BaseTurnRate = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float BaseLookUpRate = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = Telekinesis)
	float TelekinesisRange = 3000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Telekinesis)
	float TelekinesisVelocity = 5000.0f;

	bool GetAimDirection(FVector& AimDirection); //has an out param

	UFUNCTION(BlueprintCallable, Category = Telekinesis)
	class AMeteor* PullMeteor();

	UFUNCTION(BlueprintCallable, Category = Telekinesis)
	void ReleaseMeteor(AActor* HeldMeteor);

};
