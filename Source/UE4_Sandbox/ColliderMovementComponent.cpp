// Fill out your copyright notice in the Description page of Project Settings.

#include "ColliderMovementComponent.h"




void UColliderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check to make sure everything is still valid
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
		return;
	}

	// Get and clear the vector from Collider
	FVector desiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.f) * DeltaTime * 150.f; // Returns and sets it to zero
	if (!desiredMovementThisFrame.IsNearlyZero()) {
		FHitResult hit;
		SafeMoveUpdatedComponent(desiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, hit);

		// If we bump into something, slide along the side of it
		if (hit.IsValidBlockingHit()) {
			SlideAlongSurface(desiredMovementThisFrame, 1.f - hit.Time, hit.Normal, hit);
		}
	}
}
