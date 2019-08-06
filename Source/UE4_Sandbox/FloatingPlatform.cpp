// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	StartPoint = FVector::ZeroVector;
	EndPoint = FVector::ZeroVector;

	InterpSpeed = 4.f;
	InterpTime = 1.f;

	bIsInterping = false;
}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartPoint = GetActorLocation();
	EndPoint += StartPoint;

	GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, InterpTime);

	TotalDistance = (EndPoint - StartPoint).Size();
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsInterping){
		FVector currentLocation = GetActorLocation();
		FVector interp = FMath::VInterpTo(currentLocation, EndPoint, DeltaTime, InterpSpeed);
		SetActorLocation(interp);

		float distanceTraveled = (GetActorLocation() - StartPoint).Size();
		if (TotalDistance - distanceTraveled <= 1.f) {
			ToggleInterping();
			GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, InterpTime);
			SwapVectors(StartPoint, EndPoint);
		}
	}
}

void AFloatingPlatform::ToggleInterping() {
	bIsInterping = !bIsInterping;
}

void AFloatingPlatform::SwapVectors(FVector &v1, FVector &v2) {
	FVector vTemp = v1;
	v1 = v2;
	v2 = vTemp;
}


