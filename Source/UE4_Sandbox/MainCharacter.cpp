// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupCamSpringArm();
	SetupCamera();
	SetupControls();
	SetupCharacterComponent();
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

void AMainCharacter::SetupCamera()
{
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AMainCharacter::SetupCamSpringArm()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;	// Rotate arm based off Pawn controller
}

void AMainCharacter::SetupControls()
{
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
}

void AMainCharacter::SetupCharacterComponent()
{
	// Set size for collision capsule
	GetCapsuleComponent()->SetCapsuleSize(34.f, 88.f);

	// Character will automatically turn towards movement direction
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);	// Yaw is defined so only the Yaw is used for rotating orientation
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.25f;
}

