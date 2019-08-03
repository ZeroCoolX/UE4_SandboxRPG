// Fill out your copyright notice in the Description page of Project Settings.

#include "SecretSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

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
}

// Called when the game starts or when spawned
void ASecretSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	// Overlap delegates setup
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASecretSwitch::OnTriggerActivated);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASecretSwitch::OnTriggerDeactivated);
}

// Called every frame
void ASecretSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASecretSwitch::OnTriggerActivated(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Trigger Activated..."));
}

void ASecretSwitch::OnTriggerDeactivated(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndext)
{
	UE_LOG(LogTemp, Warning, TEXT("...Trigger Deactivated"));
}

