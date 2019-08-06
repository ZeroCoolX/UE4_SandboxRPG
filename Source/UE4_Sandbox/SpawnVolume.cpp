// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Critter.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetSpawnPoint()
{
	// Stores information about the dimensions of the box
	FVector extent = SpawningBox->GetScaledBoxExtent();
	FVector origin = SpawningBox->GetComponentLocation();

	// Calculate random point within confides of the box
	FVector spawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(origin, extent);
	return spawnPoint;
}

// Blueprint Native Event
void ASpawnVolume::Spawn_Implementation(UClass* spawnPawn, const FVector& spawnLocation) {
	if (spawnPawn) {
		UWorld* world = GetWorld();
		FActorSpawnParameters spawnParams;

		if (world) {
			ACritter* spawned = world->SpawnActor<ACritter>(spawnPawn, spawnLocation, FRotator::ZeroRotator, spawnParams);
		}
	}
}

