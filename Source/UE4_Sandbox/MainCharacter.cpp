// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;	// Rotate arm based off Pawn controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Stop the code unless the input component is valid
	check(PlayerInputComponent);

	// Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Movement
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::MoveRight);

	// Camera movement via key
	PlayerInputComponent->BindAxis(TEXT("TurnAtRate"), this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis(TEXT("LookUpAtRate"), this, &AMainCharacter::LookUpAtRate);

	// Camera movement via mouse
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
}

void AMainCharacter::MoveForward(float dir)
{
	// Always move in the forward direction based on wherever the camera front is pointing
	if (Controller && dir != 0.f) {
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0.f, rotation.Yaw, 0.f);

		// Rotation matrix has unit axies in x,y,z which is like accessing the local coordinate system
		const FVector facingDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		
		AddMovementInput(facingDir, dir);
	}
}

void AMainCharacter::MoveRight(float dir)
{
	// Always move in the side direction based on wherever the camera front is pointing
	if (Controller && dir != 0.f) {
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0.f, rotation.Yaw, 0.f);

		// Rotation matrix has unit axies in x,y,z which is like accessing the local coordinate system
		const FVector facingDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(facingDir, dir);
	}
}

void AMainCharacter::TurnAtRate(float rate)
{
	// Rotates controller yaw
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookUpAtRate(float rate)
{
	// Rotates controller pitch
	AddControllerPitchInput(rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


