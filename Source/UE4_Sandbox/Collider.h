// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Collider.generated.h"

UCLASS()
class UE4_SANDBOX_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USphereComponent* SphereComponent;


	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UColliderMovementComponent* MovementComponent;

	virtual  UPawnMovementComponent* GetMovementComponent() const override;

	// Accessors / Mutators
	FORCEINLINE UStaticMeshComponent* GetMeshComponent(){ return MeshComponent; }
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* mesh) { MeshComponent = mesh; }

	FORCEINLINE USphereComponent* GetSphereComponent() { return SphereComponent; }
	FORCEINLINE void SetSphereComponent(USphereComponent* sphereComp) { SphereComponent = sphereComp; }

	FORCEINLINE UCameraComponent* GetCameraComponent() { return Camera; }
	FORCEINLINE void SetCameraComponent(UCameraComponent* cam) { Camera = cam; }

	FORCEINLINE USpringArmComponent* GetSpringArmComponent() { return SpringArm; }
	FORCEINLINE void SetSpringArmComponent(USpringArmComponent* springArm) { SpringArm = springArm; }

private:
	// movement
	void MoveForward(float dir);
	void MoveRight(float dir);
	
	// camera
	void PitchCamera(float amt);
	void YawCamera(float amt);

	FVector2D CameraInput;
};
