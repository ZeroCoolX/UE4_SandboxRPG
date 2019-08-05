// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecretSwitch.generated.h"

UCLASS()
class UE4_SANDBOX_API ASecretSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASecretSwitch();

	// Logical area for which player can overlap with
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SecretSwitch)
	class UBoxComponent* TriggerBox;

	// visual area for the switch
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SecretSwitch)
	UStaticMeshComponent* PhysicalSwitch;

	// Thing that gets "activated" upon trigger overlap
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SecretSwitch)
	UStaticMeshComponent* ActivatedTarget;

	UPROPERTY(BlueprintReadWrite, Category = SecretSwitch)
	FVector InitialTargetLocation;

	UPROPERTY(BlueprintReadWrite, Category = SecretSwitch)
	FVector InitialSwitchLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()	// must be a UFUNCTION to act as a delegate
	void OnTriggerActivated(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()	// must be a UFUNCTION to act as a delegate
	void OnTriggerDeactivated(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndext);
	
	UFUNCTION(BlueprintImplementableEvent, Category = SecretSwitch)
	void ActivateTarget();

	UFUNCTION(BlueprintImplementableEvent, Category = SecretSwitch)
	void DeactivateTarget();

	UFUNCTION(BlueprintCallable, Category = SecretSwitch)
	void UpdateTargetLocation(float z);

	UFUNCTION(BlueprintImplementableEvent, Category = SecretSwitch)
	void ActivateSwitch();

	UFUNCTION(BlueprintImplementableEvent, Category = SecretSwitch)
	void DeactivateSwitch();

	UFUNCTION(BlueprintCallable, Category = SecretSwitch)
	void UpdateSwitchLocation(float z);
};
