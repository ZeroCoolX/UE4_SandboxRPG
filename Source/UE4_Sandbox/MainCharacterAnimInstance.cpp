// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	if (CharacterPawn == nullptr) {  
		CharacterPawn = TryGetPawnOwner();
	}
}

void UMainCharacterAnimInstance::UpdateAnimationProperties()
{
	// Safety check
	if (CharacterPawn == nullptr) {
		CharacterPawn = TryGetPawnOwner();
	}

	if (CharacterPawn) {
		// Update movement speed
		FVector speed = CharacterPawn->GetVelocity();
		FVector lateralSpeed = FVector(speed.X, speed.Y, 0.f);
		MovementSpeed = lateralSpeed.Size();

		// Update air property
		bIsInAir = CharacterPawn->GetMovementComponent()->IsFalling();
	}
}
