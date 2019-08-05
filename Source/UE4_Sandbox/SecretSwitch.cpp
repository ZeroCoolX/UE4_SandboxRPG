// Fill out your copyright notice in the Description page of Project Settings.

#include "SecretSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
ASecretSwitch::ASecretSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	// Ignore all collision
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	// Only allow overlap collision from pawn
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerBox->SetBoxExtent(FVector(62.f, 62.f, 32.f));

	PhysicalSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSwitch"));
	PhysicalSwitch->SetupAttachment(GetRootComponent());

	ActivatedTarget = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActivatedTarget"));
	ActivatedTarget->SetupAttachment(GetRootComponent());

	SwitchDeactivationTime = 2.f;
	bPlayerOnSwitch = false;
}

// Called when the game starts or when spawned
void ASecretSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	// Overlap delegates setup
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASecretSwitch::OnTriggerActivated);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASecretSwitch::OnTriggerDeactivated);

	InitialTargetLocation = ActivatedTarget->GetComponentLocation();
	InitialSwitchLocation = PhysicalSwitch->GetComponentLocation();
}

// Called every frame
void ASecretSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASecretSwitch::OnTriggerActivated(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Trigger Activated..."));
	bPlayerOnSwitch = true;
	ActivateTarget();
	ActivateSwitch();
}

void ASecretSwitch::OnTriggerDeactivated(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndext)
{
	UE_LOG(LogTemp, Warning, TEXT("...Trigger Deactivated"));
	bPlayerOnSwitch = false;
	GetWorldTimerManager().SetTimer(SwitchHandle, this, &ASecretSwitch::BeginTargetDeactivation, SwitchDeactivationTime);
}

void ASecretSwitch::BeginTargetDeactivation()
{
	if (!bPlayerOnSwitch) {
		DeactivateTarget();
		DeactivateSwitch();
	}
}

void ASecretSwitch::UpdateTargetLocation(float z)
{
	FVector newLocation = InitialTargetLocation;
	newLocation.Z += z;
	ActivatedTarget->SetWorldLocation(newLocation);
}

void ASecretSwitch::UpdateSwitchLocation(float z)
{
	FVector newLocation = InitialSwitchLocation;
	newLocation.Z += z;
	PhysicalSwitch->SetWorldLocation(newLocation);
}

