// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class UE4_SANDBOX_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner)
	class UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawner)
	TSubclassOf<class ACritter> SpawningPawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = Spawner)
	FVector GetSpawnPoint();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Spawner)
	void Spawn(UClass* spawnPawn, const FVector& spawnLocation);
	
};
