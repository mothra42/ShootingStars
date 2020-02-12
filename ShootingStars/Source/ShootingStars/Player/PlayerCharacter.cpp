// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "../HUD/ShootingStarsHUD.h"
#include "Components/SceneComponent.h"
#include "../Props/Meteor.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	TelekinesisHoldPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TelekinesisHoldPoint"));
	TelekinesisHoldPoint->SetupAttachment(Super::GetCapsuleComponent());
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		//find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

USpringArmComponent* APlayerCharacter::GetCameraBoom() const
{
	return CameraBoom;
}

UCameraComponent* APlayerCharacter::GetCameraComponent() const
{
	return CameraComponent;
}

bool APlayerCharacter::GetAimDirection(FVector& AimDirection)
{
	auto HUD = PlayerController->GetHUD();
	AShootingStarsHUD* ShootingStarsHUD = Cast<AShootingStarsHUD>(HUD);

	if (ShootingStarsHUD != nullptr)
	{
		auto CrosshairLocation = ShootingStarsHUD->GetCrosshairDrawPosition();

		FVector WorldLocation;
		if (PlayerController != nullptr)
		{
			return PlayerController->DeprojectScreenPositionToWorld(
				CrosshairLocation.X,
				CrosshairLocation.Y,
				WorldLocation,
				AimDirection
			);
		}
	}

	return false;
}

AMeteor* APlayerCharacter::PullMeteor()
{
	FVector AimDirection;
	if (GetAimDirection(AimDirection))
	{
		FHitResult HitResult;
		auto StartLocation = CameraComponent->GetComponentLocation();
		auto EndLocation = StartLocation + (AimDirection.GetSafeNormal() * TelekinesisRange);
		
		if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility
		))
		{
			AActor* CapturedMeteor = HitResult.GetActor();
			return Cast<AMeteor>(CapturedMeteor);
		}
	}

	return nullptr;
}

void APlayerCharacter::ReleaseMeteor(AActor* HeldMeteor)
{
	if (HeldMeteor != nullptr)
	{
		AMeteor* Meteor = Cast<AMeteor>(HeldMeteor);
		if (Meteor != nullptr)
		{
			FVector AimDirection;
			if (GetAimDirection(AimDirection))
			{
				UProjectileMovementComponent* ProjectileMovement = Meteor->ProjectileMovement;

				ProjectileMovement->Velocity = (AimDirection.GetSafeNormal() * 5000);
			}
		}
	}
}